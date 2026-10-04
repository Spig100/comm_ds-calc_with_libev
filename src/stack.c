#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool isEmpty (const stack * const stackPtr) {
	if (stackPtr->top == -1) return true;
	return false;
}

bool isOverflow (const stack * const stackPtr){
	if (stackPtr->top == STACK_MAX_SIZE-1) return true;
	return false;
}

int8_t int_stack_pop (stack * const stackPtr){
	if (isEmpty(stackPtr)){
		printf("DEBUG: stack underflow.");
		return -1;
	}
	int8_t result = stackPtr->content[stackPtr->top --];
	return result;
}

uint8_t int_stack_push (stack * const stackPtr, int8_t x){
	if (isOverflow(stackPtr)) {
		printf("DEBUG: stack overflow.");
		return 1;
	}
	stackPtr->content[++ stackPtr->top] = x;
	return 0;
}

int8_t int_stack_top (const stack * const stackPtr){
	return stackPtr->top;

}

bool char_isEmpty (const char_stack * const stackPtr){
	if (stackPtr->top == -1) return true;
	return false;
}

bool char_isOverflow (const char_stack * const stackPtr){
	if (stackPtr->top == STACK_MAX_SIZE-1) return true;
	return false;
}

uint8_t char_pop (char_stack * const stackPtr){
	if (isEmpty(stackPtr)){
		printf("DEBUG: stack underflow.");
		return -1;
	}
	int8_t result = stackPtr->content[stackPtr->top --];
	return result;
}

uint8_t char_push (char_stack * const stackPtr, char x){
	if (isOverflow(stackPtr)) {
		printf("DEBUG: stack overflow.");
		return 1;
	}
	stackPtr->content[++ stackPtr->top] = x;
	return 0;
}

char char_top (const int_stack * const stackPtr){
	return stackPtr->top;
}
