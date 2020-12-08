#ifndef _PLATE_H
#define _PLATE_H
#include "lists.h"

typedef struct cases cases;

typedef cases** plate;

void print_plate_state(plate p);

plate create_empty_plate();

void deactivate_all(plate *p);

int oob(int i, int j);

void print_cases(int i, int j, plate p);

int place_at(int player, int i, int j, plate *p, int n);

int is_plate_full(plate p);

int* count_score(plate p);

plate copy_plate(plate p);

void destroy_plate(plate p);

#endif  