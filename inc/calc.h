#ifndef CALC_H
#define CALC_H

#define MAX_NUM_STR_LENGTH 64 /* Setup a reasonable value for it to avoid segmentation fault. */

#include <ev.h>
#include "stack.h"

double add (double x, double y);
double substract (double x, double y);
double multiply (double x, double y);
double divide (double x, double y);

uint8_t precedence(char op);

typedef double (*Operation) (double, double);

Operation get_operation (char opr);

int flush_operator (num_stack * operand, char_stack * operater);
double calculate(const char * const expression);

#endif
