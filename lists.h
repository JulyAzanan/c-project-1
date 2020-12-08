#ifndef _LISTS_H
#define _LISTS_H


typedef struct cell* list;

list create_empty();

int is_empty(list l);

void push(int value, list *l);

int pop(list *l);

void pretty_print(list l);

int mem (int value, list l);

void remove_one (int value, list *l);

void reset(list *l); 

int head(list l);

void copy(list l, list *l2);

#endif