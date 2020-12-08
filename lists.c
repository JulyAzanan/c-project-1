#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

struct cell {
    int value;
    struct cell *next;
};

typedef struct cell* list;

/**
*Requires : nothing
*Assigns : nothing
*Ensures : returns a new empty list (NULL)
*/
list create_empty() {
    return NULL;
}

/**
*Requires : a list l
*Assigns : nothing
*Ensures : returns 1 if the list is empty
*/
int is_empty(list l) {
    return l == NULL;
}

/**
*Requires : a value and a pointer to a list
*Assigns : a new cell of the list
*Ensures : push value at the head of the list
*/
void push(int value, list *l) {
    list tmp = malloc(sizeof(struct cell));
    tmp->value = value;
    tmp->next = *l;
    *l = tmp;
}

/**
*Requires : a list 
*Assigns : nothing
*Ensures : returns the value at the head of the list and remove it from the list. returns -1 if the list is empty
*/
int pop(list *l) {
    if (*l == NULL) return -1; //valeur par défaut
    int value = (*l)->value;
    list tmp = *l;
    *l = (*l)->next;
    free(tmp);
    return value;
}

/**
*Requires : a list 
*Assigns : nothing
*Ensures : prints the list in a fancy way (like a pile of plate)
*/
void pretty_print(list l) {
    //loop invariant : l is not cylic so it only has a finite number of element
    while (l != NULL) {
        printf("%3i\n", l->value);
        l = l->next;
    }
    printf("---\n");
}

/**
*Requires : a value and a list
*Assigns : nothing
*Ensures : returns 1 if value is inside of l, and 0 if else
*/
int mem (int value, list l) {
    //loop invariant : l is not cylic so it only has a finite number of element
    while (l != NULL) {
        if (value == l->value) return 1;
        l = l->next;
    }
    return 0;
}

/**
*Requires : a value and a pointer to a list
*Assigns : curr and next
*Ensures : remove the first element value of the list, if there is at least one inside of it
*/
void remove_one (int value, list *l) {
    if (!mem(value, *l)) return;    //sort de la fonction si liste vide ou bien que value n'est pas dedans
    list curr = *l;
    list next = (*l)->next;
    if (curr->value == value) { //cas où la valeur à enlever est en tête
        free(curr);
        *l = next;
        return;
    }
    //loop invariant : l is not cylic so it only has a finite number of element
    while (next != NULL) { //cas où la valeur à enlever est dans le corps de la liste
        if (next->value == value) {
            list tmp = next;
            curr->next = next->next;
            free(tmp);
            return;
        }
        curr = curr->next;
        next = next->next;
    }
}

/**
*Requires : a pointer to a list l
*Assigns : nothing
*Ensures : resets completly the list, frees everything, and set the list to NULL (empty list)
*/
void reset(list *l) { 
    //loop invariant : l is not cylic so it only has a finite number of element
    while (*l != NULL) {
        list tmp = *l;
        *l = (*l)->next;
        free(tmp);
    }
    *l = NULL;
}

/**
*Requires : a list
*Assigns : nothing
*Ensures : returns the value of the head of the list, or -1 if the list is empty
*/
int head(list l) {
    if (l == NULL) return -1;
    return l->value;
}

/**
*Requires : l2 is set to NULL
*Assigns : a new list l2
*Ensures : returns a new list that is the copy of l
*/
void copy(list l, list *l2) {
    if (l == NULL) return;
    push(l->value, l2);
    l = l->next;
    list tmp = (*l2)->next;
    while (l != NULL) {
        push(l->value, &tmp);
        tmp = tmp->next;
        l = l->next;
    }
}