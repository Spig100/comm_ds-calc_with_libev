#ifndef CALC_H
#define CALC_H

#include <ev.h>
#include "stack.h"

double add (double x, double y);
double substract (double x, double y);
double multiply (double x, double y);
double divide (double x, double y);

typedef double (*Operation) (double, double);

Operation get_operation (char opr);

void calculate(int_stack * const operand, char_stack * const operators);

#endif
