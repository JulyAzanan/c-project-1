#include <stdio.h>
#include <stdlib.h>
#include "plate.h"
#include "lists.h"

struct move {
    int x;
    int y;
    int value_for_self;
    int value_for_ennemy;
};

typedef struct move move;

extern plate p_g;
extern int size;
//plate p_copy;

/**
*Requires : nothing
*Assigns : a move m
*Ensures : returns an empty move
*/
move init_move() {
    move m;
    m.x = 0;
    m.y = 0;
    m.value_for_self = 0;
    m.value_for_ennemy = 0;
    return m;
}

/**
*Requires : nothing
*Assigns : nothing
*Ensures : complete the move m
*/
void test_move(move *m, plate p) {
    int *r = count_score(p);
    m->value_for_ennemy = r[0];
    m->value_for_self = r[1];
    free(r);
}

/**
*Requires : a valid coordinate x and y
*Assigns : the move m associated
*Ensures : returns the move m associated to x and y
*/
move pre_move(int x, int y) {
    move m = init_move();
    m.x = x;
    m.y = y;
    plate p_copy = copy_plate(p_g);
    place_at(2, x, y, &p_copy, 1);
    test_move(&m, p_copy);
    destroy_plate(p_copy);
    return m;
}

/**
*Requires : a list of move of size size*size
*Assigns : nothing
*Ensures : ensures that mini_ennemy and max_self now contains the indices of the moves : one that gives the minimum score to the ennemy and the others the maximum score for the AI
*/
void minimax(move *m, int *mini_ennemy, int *max_self) {
    *mini_ennemy = 0;
    *max_self = 0;
    int stop = size*size;
    for (int i = 1; i < stop; i++) {
        if (m[*mini_ennemy].value_for_ennemy > m[i].value_for_ennemy) *mini_ennemy = i;
        if (m[*max_self].value_for_self < m[i].value_for_self) *max_self = i;
    }
}

void update_ai() {
    move *move_list = malloc(size*size*sizeof(move));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            move_list[size*i + j] = pre_move(i + 1, j + 1);
        }
    }
    int mini = 0;
    int maxi = 0;
    minimax(move_list, &mini, &maxi);
    int diff_score_max = move_list[maxi].value_for_self - move_list[maxi].value_for_ennemy;
    int diff_score_min = move_list[mini].value_for_self - move_list[mini].value_for_ennemy;
    if (diff_score_max > diff_score_min) { //Omega will do the move that's the best for her and the worst for the player.
        place_at(2, move_list[maxi].x, move_list[maxi].y, &p_g, 1);
        printf("Omega a placé son pion en %i %i avec le choix maxi.\n", move_list[maxi].x, move_list[maxi].y);
    }
    else {
        place_at(2, move_list[mini].x, move_list[mini].y, &p_g, 1);
        printf("Omega a placé son pion en %i %i avec le choix mini.\n", move_list[mini].x, move_list[mini].y);
    }
    print_plate_state(p_g);
    deactivate_all(&p_g);
    free(move_list);
    printf("A toi de jouer, humain. Sauras-tu contrer ce coup d'Omega ?\n");
}