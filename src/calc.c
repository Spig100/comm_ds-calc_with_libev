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

void flush_operator(num_stack * const operand, char_stack * const operator){
    int a, b;
    while (!char_stack_isEmpty(operator)){
        b = num_stack_pop(operand);
        a = num_stack_pop(operand);
        num_stack_push(operand, get_operation(char_stack_pop(operator))(a, b));
    }
}

double calculate(const char * const expression){
    char_stack operator;
    num_stack operand;

    uint32_t index = 0;
    
    bool isMD = false;

    while(expression[index] != '\0'){
        switch(expression[index]){
            case ' ':
                break;
            case '+':
            case '-':
                if (isMD) 
                break;
            case '*':
            case '/':
                break;
        }
    }

    return num_stack_top(&operand);

}

