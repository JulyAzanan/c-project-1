#include <stdio.h>
#include <stdlib.h>
#include "lists.h"
#include "plate.h"

int size = 5;   //global variable representing the size (length OR width) of the game pleteau
int nb_player = 2;  //global variable representing the number of players

struct cases {
    int activated;
    list l;
};

typedef struct cases cases;
typedef cases** plate;

/**
*Requires : a plate p
*Assigns : nothing
*Ensures : prints the current state of the plate in a fancy way
*/
void print_plate_state(plate p) {
    printf("   |");
    for (int i = 0; i < size; i++) {
        printf("%3i", i+1);
    }
    printf("\n");
    printf("---+");
    for (int i = 0; i < size; i++) {
        printf("---");
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%3i|", i+1);
        for (int j = 0; j < size; j++) {
            if (is_empty(p[i][j].l)) printf("   ");
            else printf("%3i", head(p[i][j].l));
        }
        printf("\n");
    }
    printf("\n");
}

/**
*Requires : nothing
*Assigns : a plate of size (size*size)
*Ensures : returns a new empty plate
*/
plate create_empty_plate() {
    plate new_plate = malloc(size*sizeof(cases));
    for (int i = 0; i < size; i++) {
        new_plate[i] = malloc(size*sizeof(cases));
        for (int j = 0; j < size; j++) {
            new_plate[i][j].l = create_empty();
            new_plate[i][j].activated = 0;
        }
    }
    print_plate_state(new_plate);
    return new_plate;
}

/**
*Requires : a pointer to a plate p
*Assigns : nothing
*Ensures : turns all casses to their deactivated state
*/
void deactivate_all(plate *p) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            (*p)[i][j].activated = 0;
        }
    }
}

/**
*Requires : i and j
*Assigns : nothing
*Ensures : 1 if the region specified by i and j is Out Of Bounds, and 0 if it is fine
*/
int oob(int i, int j) {
    return (i > size || j > size || i < 1 || j < 1);
}

/**
*Requires : nothing
*Assigns : nothing
*Ensures : prints the content of the case in a pretty format
*/
void print_cases(int i, int j, plate p) {
    if (!oob(i, j)) pretty_print(p[i-1][j-1].l);
}

/**
*Requires : a player id, i, j and a plate, and n, which indicates if it's from a chain (0) or from a player input (1) and a list remembering all the activated cases during the turn
*Assigns : nothing
*Ensures : returns 1 and update p if it could place successfully, and 0 if else
*/
int place_at(int player, int i, int j, plate *p, int n) {
    //printf("%i %i\n", i, j);
    //stop case : the case is out of bounds, or it has already been activated
    if (oob(i, j) || (*p)[i-1][j-1].activated) {
        if (n) printf("Les valeurs entrées ne correspondent pas. Rappel : 1 <= valeurs <= %i\n", size);
        //printf("not placed at %i %i\n", i, j);
        return 0;
    }
    if (player ==  head((*p)[i-1][j-1].l)) {
        remove_one(player, &((*p)[i-1][j-1].l));
        (*p)[i-1][j-1].activated = 1;
        //printf("Activating %i %i\n", i, j);
        place_at(player, i-1, j, p, 0);
        place_at(player, i+1, j, p, 0);
        place_at(player, i, j-1, p, 0);
        place_at(player, i, j+1, p, 0);
        return 1;
    }
    push(player, &((*p)[i-1][j-1].l));
    //printf("Placed at %i %i\n", i, j);
    return 1;
}

/**
*Requires : a plate p
*Assigns : nothing
*Ensures : returnes 1 if the plate is full, and 0 if else
*/
int is_plate_full(plate p) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (is_empty(p[i][j].l)) return 0;
        }
    }
    return 1;
}

/**
*Requires : a plate p (full)
*Assigns : a array of int of size nb_player
*Ensures : returns the list of the scores of each player
*/
int* count_score(plate p) {
    int* scores = malloc(nb_player*sizeof(int));
    for (int i = 0; i < nb_player; i++) scores[i] = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scores[head(p[i][j].l) - 1]++;
        }
    }
    return scores;
}

/* int main() {
    plate p = create_empty_plate();
    place_at(1, -1, 2, &p, 1);
    print_plate_state(p);
    deactivate_all(&p);
    place_at(2, 5, 1, &p, 1);
    print_plate_state(p);
    deactivate_all(&p);
    place_at(2, 5, 1, &p, 1);
    deactivate_all(&p);
    print_plate_state(p);
    pretty_print(p[0][0].l);
    return 0;
}
 */