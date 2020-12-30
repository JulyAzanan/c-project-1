#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plate.h"
#include "lists.h"
#include "AI.h"

extern int nb_player; //global variable present in plate.c
extern int size; //global variable present in plate.c
extern int p_turn; //global variable indicating whose turn it is to play present in plate.c
extern plate p_g; //global variable representing the game plateau present in plate.c
int no_winner = 1; //global variable indicating if someone has already won
extern int difficulty;

/**
*Requires : asks the player to enter ONE numeric value > to condition
*Assigns : a buffer of size 256
*Ensures : prompts the player something specified by the ask variable, and if it is in the correct format, modifies the value of *var. Loops while the player input is not in the correct format
*/
void ask_player_one_thing(char *ask, int* var, int condition) {
    char buf[256];
    //Loop invariant : the player will end prompting a correct value
    do {
        printf("%s\n", ask);
        fgets(buf, 256, stdin);
    } while (sscanf(buf, "%i\n", var) != 1 || *var <= condition);
}

/**
*Requires : nothing
*Assigns : a plate p
*Ensures : returns an empty plate of dimension given by the user and for the amount of player given by the user
*/
plate init() {
    ask_player_one_thing("Veuillez entrer un nombre de joueurs.", &nb_player, 0);
    ask_player_one_thing("Veuillez entrer une taille de terrain.", &size, 1);
    if (nb_player == 1) ask_player_one_thing("Veuillez sélectionner la difficulté de l'intelligence artificielle. (0 = difficile, sinon facile.)", &difficulty, -1);
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
        printf("%8i ", a[i]);
    }
    printf("\n");
}

/**
*Requires : nothing
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
*Assigns : modifies the value of the global variable no_winner
*Ensures : detect if the game is over, announce the ranking and finish the game (and the program)
*/
void detect_victory() {
    if (is_plate_full(p_g)) {
        no_winner = 0;
        print_results(count_score(p_g));
        return;
    }
}

/**
*Requires : nothing
*Assigns : a lot of things
*Ensures : play the turn of one player
*/
void update() {
    printf("C'est au tour du joueur %i de jouer.\n", p_turn);
    char buf[256];
    int x = -1;
    int y = -1;
    int validate = 0;
    //loop invariant : the loop will end when the user will prompt a valid cell coordinate and confirm their choice
    while (!validate) {
        printf("Veuillez sélectionner une case. Format attendu : x y.\n");
        if (fgets(buf, 256, stdin) == NULL) {
            printf("EOF rencontré dans stdin. Arrêt prématuré du jeu.\n");
            fflush(stdout);
            exit(0);
        }
        if (sscanf(buf, "%i %i", &x, &y) != 2) continue;
        if (!oob(x, y)) {
            printf("\n");
            print_cases(x, y, p_g);
        }
        else {
            printf("Les valeurs entrées ne correspondent pas. Rappel : 1 <= valeurs <= %i\n", size);
            continue;
        }
        printf("Confirmez vous le choix de placer en %i %i ?(o/n)\n", x, y);
        fgets(buf, 256, stdin);
        if (compare_strings(buf, "o")) {
            if (place_at(p_turn, x, y, &p_g, 1))
                validate = 1;
        }
    }
    print_plate_state(p_g);
    deactivate_all(&p_g);
    p_turn = p_turn >= nb_player ? 1 : p_turn + 1;
}

int main() {
    p_g = init();
    print_plate_state(p_g);
    //loop invariant : the game will finish when all case will be filled with at least one item
    if (nb_player > 1) {
        while(no_winner) {
            update();
            detect_victory();
        }
    }
    else {
        nb_player = 2;
        init_taunts();
        printf("Mode solo : vous allez affronter Omega en difficulté %i.\n", difficulty);
        srand(time(NULL));
        p_turn = rand_between(1, 2);
        if (p_turn == 2) {
            printf("C'est Omega qui commence\n");
            first_to_play();
            //detect_victory() not needed because the plate is of size 2 at least
        }
        //loop invariant : idem
        while(no_winner) {
            update();
            detect_victory();
            if (!no_winner) break;
            update_ai();
            detect_victory();
        }
    }
    return 0;
}
