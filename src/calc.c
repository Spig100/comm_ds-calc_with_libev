#include "calc.h"
#include "stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <ev.h>

double add (double x, double y){
    return x + y;
}

double substract (double x, double y){
    return x - y;
}

double multiply (double x, double y){
    return x * y;
}

double divide (double x, double y){
    if (y == 0) return NAN;
    return x / y;
}

Operation get_operation (char opr){
    switch(opr){
        case '+':
            return add;
            break;
        case '-':
            return substract;
            break;
        case '*':
            return multiply;
            break;
        case '/':
            return divide;
            break;
        default:
            return NULL;
            break;
    }
}

void calculate(int_stack * const operand, char_stack * const operator){
    int8_t a;
    int8_t b;
    Operation operate;
    while (!char_stack_isEmpty(operator)){
        b = int_stack_pop(operand);
        a = int_stack_pop(operand);
        operate = get_operation(char_stack_pop(operator));
        int_stack_push(operand, operate(a,b));
    }
}

