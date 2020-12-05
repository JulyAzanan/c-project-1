#include <stdio.h>
#include <stdlib.h>
#include "plate.h"
#include "lists.h"

extern int nb_player; //global variable present in plate.c
extern int size; //global variable present in plate.c
int p_turn = 0; //global variable indicating whose turn it is to play
plate p; //global variable representing the game plateau
int no_winner = 1; //global variable indicating if someone has already won

/**
*Requires : nothing
*Assigns : a plate p
*Ensures : returns an empty plate of dimension given by the user and for the amount of player given by the user
*/
plate init() {
    char buf[256];
    //loop invariant : the user will end to enter an integer > 1.
    do {
        printf("Veuillez entrer un nombre de joueurs.\n");
        fgets(buf, 256, stdin);
    } while (sscanf(buf, "%i\n", &nb_player) != 1 && nb_player > 1);
    //loop invariant : idem
    do {
        printf("Veuillez entrer une taille de terrain.\n");
        fgets(buf, 256, stdin);
    } while (sscanf(buf, "%i\n", &size) != 1 && size > 1);
    p_turn = 1;
    return create_empty_plate();
}

/**
*Requires : an array of int of size nb_player
*Assigns : nothing 
*Ensures : prints the result of the game
*/
void print_results(int* a) {
    printf("Résultats : \n");
    for (int i = 0; i < nb_player; i++) {
        printf("joueur %i ", i+1);
    }
    printf("\n");
    for (int i = 0; i < nb_player; i++) {
        printf("       %i ", a[i]);
    }
    printf("\n");
}

/**
*Requires : an array of size nb_player and the pointers to 2 int
*Assigns : modify the value of value and i
*Ensures : i is the player who won the game, and value their score
*/
void max_score(int *a, int *value, int *i) {
    *i = 0;
    for (int j = 1; j < nb_player; j++) { //ne traite pas le cas des égalités 
        *i = a[*i] < a[j] ? j : *i;
    }
    *value = a[*i];
}

/**
*Requires : a player id and their score
*Assigns : nothing
*Ensures : announce the winner officially 
*/
void winner(int i, int value) {
    printf("Le.a grand.e gagnant.e est joueur.euse %i avec un score de %i\n", i+1, value);
}

/**
*Requires : 2 strings
*Assigns : nothing
*Ensures : returns 1 if the string s1 begin like (or is equal to) the string s2 (or the opposite : s2 begin like or is equal to s1) and 0 if else
*/
int compare_strings(char *s1, char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return 0;
        i++;
    }
    return 1;
}

/**
*Requires : nothing
*Assigns : a lot of things
*Ensures : play the turn of one player, and check if the game is over
*/
void update() {
    printf("C'est au tour du joueur %i de jouer.\n", p_turn);
    char buf[256];
    int x = -1;
    int y = -1;
    int validate = 0;
    //loop invariant : the loop will end when the user will prompt a valid case coordinate and confirm their choice
    while (!validate) {
        printf("Veuillez sélectionner une case. Format attendu : x y\n");
        fgets(buf, 256, stdin);
        if (sscanf(buf, "%i %i", &x, &y) != 2) continue;
        if (!oob(x, y)) {
            printf("\n");
            print_cases(x, y, p);
        }
        else {
            printf("Les valeurs entrées ne correspondent pas. Rappel : 1 <= valeurs <= %i\n", size);
            continue;
        }
        printf("Confirmez vous le choix de placer en %i %i ?(o/n)\n", x, y);
        fgets(buf, 256, stdin);
        if (compare_strings(buf, "o")) {
            if (place_at(p_turn, x, y, &p, 1))
                validate = 1;
        }
    }
    if (is_plate_full(p)) {
        no_winner = 0;
        print_results(count_score(p));
        int i = 0;
        int score = 0;
        max_score(count_score(p), &score, &i);
        winner(i, score);
        return;
    }
    print_plate_state(p);
    deactivate_all(&p);
    p_turn = p_turn >= nb_player ? 1 : p_turn + 1;
}

int main() {
    p = init();
    //loop invariant : the game will finish when all case will be filled with at least one item
    while(no_winner) update();
    return 0;
}
