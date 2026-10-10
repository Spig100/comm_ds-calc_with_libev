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
    double a, b;
    char op;
    while (!char_stack_isEmpty(operator)){
        b = num_stack_pop(operand);
        a = num_stack_pop(operand);
        op = char_stack_pop(operator);
        Operation operation = get_operation(op);
        num_stack_push(operand, operation(a, b));
    }
}

double calculate(const char * const expression){
    
    /* TODO: Finish the calculation function with stack (direct infix).
     * */

    num_stack operand;
    char_stack operator;

    num_stack_init(&operand);
    char_stack_init(&operator);

    int index = 0;
    
    bool isMD = false;
    bool isInvalid = false;
    
    while(expression[index] != '\0'){
        switch(expression[index]){ 
            case ' ':
                break;
            case '+':
            case '-':
                if (isMD) {
                    flush_operator(&operand, &operator);
                    isMD = false;
                }
                char_stack_push(&operator, expression[index]);
                break;
            case '*':
            case '/':
                isMD = true;
                char_stack_push(&operator, expression[index]);
                break;
            default:
                if ('0' > expression[index] || '9' < expression[index]){
                    isInvalid = true;
                }
                char num_buf[MAX_NUM_STR_LENGTH];
                int num_length = 0;
                while(isdigit(expression[index + num_length])){
                    num_buf[num_length] = expression[index + num_length];
                    num_length++;
                }
                num_buf[num_length] = '\0';
                num_stack_push(&operand, atoi(num_buf));
                index += num_length - 1;
                break;       
        }
        
        if (isInvalid) {
            printf("Invalid expression.\n\n");
            return -1;
        }

        index++;
    
    }

    flush_operator(&operand, &operator);

    printf ("Result\t\t> %g\n\n", num_stack_top(&operand));
    return num_stack_top(&operand);

}

