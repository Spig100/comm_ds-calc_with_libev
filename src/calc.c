#include "calc.h"
#include "stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <ev.h>
#include <stdlib.h>
#include <ctype.h>

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

    /* TODO: Finish the calculation function with stack (direct infix).
     * */

    num_stack operand;
    char_stack operator;

    num_stack_init(&operand);
    char_stack_init(&operator);

    uint32_t index = 0;
    
    bool isMD = false;
    
    /* FIXME: Fix the infinity loop problem.
     * */

    while(expression[index] != '\0'){
        switch(expression[index]){
            
            case ' ':
                break;
            case '+':
            case '-':
                if (isMD){
                    flush_operator(&operand, &operator);
                } 
            case '*':
            case '/':
                char_stack_push(&operator, expression[index]);
                break;
            default:
                char num_buf[MAX_NUM_STR_LENGTH];
                int num_length = 0;
                while(isdigit(expression[index])){
                    num_buf[num_length] = expression[index + num_length];
                    index++;
                }
                num_stack_push(&operand, atoi(num_buf));
                break;
                
        }

        flush_operator(&operand, &operator);

        index++;
    
    }

    return num_stack_top(&operand);

    // return num_stack_top(&operand);

}

