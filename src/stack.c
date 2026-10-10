#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void num_stack_init (num_stack * const stackPtr){
    stackPtr->top = -1;
}

bool num_stack_isEmpty (const num_stack * const stackPtr) {
	if (stackPtr->top == -1) return true;
	return false;
}

bool num_stack_isOverflow (const num_stack * const stackPtr){
	if (stackPtr->top == STACK_MAX_SIZE-1) return true;
	return false;
}

double num_stack_pop (num_stack * const stackPtr){
	if (num_stack_isEmpty(stackPtr)){
		return 0;
	}
	double result = stackPtr->content[stackPtr->top--];
	return result;
}

uint8_t num_stack_push (num_stack * const stackPtr, double x){
	if (num_stack_isOverflow(stackPtr)) {
		return 1;
	}
	stackPtr->content[++stackPtr->top] = x;
	return 0;
}

double num_stack_top (const num_stack * const stackPtr){
	return stackPtr->content[stackPtr->top];
}

void char_stack_init (char_stack * const stackPtr){
    stackPtr->top = -1;
}

bool char_stack_isEmpty (const char_stack * const stackPtr){
	if (stackPtr->top == -1) return true;
	return false;
}

bool char_stack_isOverflow (const char_stack * const stackPtr){
	if (stackPtr->top == STACK_MAX_SIZE-1) return true;
	return false;
}

char char_stack_pop (char_stack * const stackPtr){
	if (char_stack_isEmpty(stackPtr)){
		return -1;
	}
	int8_t result = stackPtr->content[stackPtr->top --];
	return result;
}

uint8_t char_stack_push (char_stack * const stackPtr, char x){
	if (char_stack_isOverflow(stackPtr)) {
		return 1;
	}
	stackPtr->content[++ stackPtr->top] = x;
	return 0;
}

char char_stack_top (const char_stack * const stackPtr){
	return stackPtr->top;
}
