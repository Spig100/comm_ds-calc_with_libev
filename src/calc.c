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

/* Note that we need to realize the flush process to make all the lower-precedence be calculated.
 *
 * Originally, I used a while-loop to flush ALL the content of the stack. But it doesn't fit the philosophy of the infix
 * process. Therefore, after the discussion with ChatGPT, I changed it to a single-round if statement.
 *
 * */

void flush_operator(num_stack * const operand, char_stack * const operator){
    char op = char_stack_pop(operator);
    //fprintf(stderr, "Debug: op flushed - %c\n", op);
    Operation operation = get_operation(op);
    if (operation == NULL) return;
    double b = num_stack_pop(operand);
    double a = num_stack_pop(operand);
    num_stack_push(operand, operation(a, b));
    //fprintf(stderr, "DEBUG: %g %c %g\n", a, op, b);
}

uint8_t precedence(char op){
    switch(op){
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
            return 2;
            break;
        case '^':
            return 3;
        default:
            return 0;
            break;

    }
}

double calculate(const char * const expression){
    
    // TODO: Finish escape sequence for segment rolling.

    num_stack operand;
    char_stack operator;

    num_stack_init(&operand);
    char_stack_init(&operator);

    int index = 0;
    
    // int indexMD = -1;
    // int isMD = false;
    bool isInvalid = false;
    bool last_operator = false;

    /* A better way to deal with the operation order is to create a function that return the 
     * order. That will make the flushing logic more simple.
     *
     * The procedure will be:
     * 1)   Once the operator is iterated, we'll call a precedence function which will return
     *      a number reflecting the precedence of the current operation.
     * 2)   Make a if-else statement to determine if we need to flush the operator or not. 
     *
     * OCT 11 with ChatGPT.
     * */

//    while(expression[index] != '\0'){
//        switch(expression[index]){ 
//            case ' ':
//                break;
//            case '+':
//            case '-':
//                if (isMD) {
//                    flush_operator(&operand, &operator);
//                    isMD = false;
//                }
//                char_stack_push(&operator, expression[index]);
//                break;
//            case '*':
//            case '/':
//                char_stack_push(&operator, expression[index]);
//                isMD = true;
//                break;
//            default:
//                if ('0' > expression[index] || '9' < expression[index]){
//                    isInvalid = true;
//                }
//                char num_buf[MAX_NUM_STR_LENGTH];
//                int num_length = 0;
//                while(isdigit(expression[index + num_length])){
//                    num_buf[num_length] = expression[index + num_length];
//                    num_length++;
//                }
//                num_buf[num_length] = '\0';
//                num_stack_push(&operand, atoi(num_buf));
//                index += num_length - 1;
//                break;       
//        }
//        
//        if (isInvalid) {
//            printf("Invalid expression.\n\n");
//            return -1;
//        }
//
//        index++;
//    
//    }

    while (expression[index] != '\0') {
        switch (expression[index]){
            case ' ':
                break;
            case '+':
            case '-':
            case '*':
            case '/':
//                if (!char_stack_isEmpty(&operator)) {
//                    char top_op = char_stack_top(&operator);
//
//                    fprintf(stderr,
//                        "CHECK: current='%c', top='%c', "
//                        "top_precedence=%d, current_precedence=%d\n",
//                        expression[index],
//                        top_op,
//                        precedence(top_op),
//                        precedence(expression[index]));
//                }
                
                if(last_operator){
                    isInvalid = true;
                    break;
                }

                last_operator = true;

                while (!char_stack_isEmpty(&operator) && 
                        precedence(char_stack_top(&operator)) >= precedence(expression[index]))
                    flush_operator(&operand, &operator);
            case '(':
                char_stack_push(&operator, expression[index]);
                break;
            case ')':
                
                while ( char_stack_top(&operator) != '(' && !char_stack_isEmpty(&operator)){
                    // fprintf(stderr, "Debug: top - %c\n", char_stack_top(&operator));
                    flush_operator(&operand, &operator);
                }

                char_stack_pop(&operator);
                break;

            default:
                if (expression[index] == '(') break;
                last_operator = false;
                if ('0' > expression[index] || '9' < expression[index]){
                    isInvalid = true;
                    break;
                }
                char num_buf[MAX_NUM_STR_LENGTH];
                int num_length = 0;
                while (isdigit(expression[index + num_length]) || 
                        expression[index + num_length] == '.'){
                    num_buf[num_length] = expression[index + num_length];
                    num_length++;
                }
                num_buf[num_length] = '\0';
                //fprintf(stderr, "PUSH: %s\n", num_buf);
                num_stack_push(&operand, atof(num_buf));
                index += num_length - 1;
                break;
        }

        if (isInvalid) {
            printf("Invalid expression.\n\n");
            return -1;
        }

        index ++;
    }


    while (!char_stack_isEmpty(&operator)) {
        flush_operator(&operand, &operator);
    }

    if (num_stack_isEmpty(&operand)){
        printf("Empty input.\n\n");
        return -1;
    }

    if ( isnan(num_stack_top(&operand)) ) {
        printf ("Division by zero.\n\n");
        return -1;
    }

    printf ("Result\t\t> %g\n\n", num_stack_top(&operand));
    return num_stack_top(&operand);

}

