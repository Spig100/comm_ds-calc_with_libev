#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool int_isEmpty (const int_stack * const stackPtr) {
	if (stackPtr->top == -1) return true;
	return false;
}

bool int_isOverflow (const int_stack * const stackPtr){
	if (stackPtr->top == STACK_MAX_SIZE-1) return true;
	return false;
}

int8_t int_stack_pop (int_stack * const stackPtr){
	if (int_isEmpty(stackPtr)){
		printf("DEBUG: stack underflow.");
		return -1;
	}
	int8_t result = stackPtr->content[stackPtr->top --];
	return result;
}

uint8_t int_stack_push (int_stack * const stackPtr, int8_t x){
	if (int_isOverflow(stackPtr)) {
		printf("DEBUG: stack overflow.");
		return 1;
	}
	stackPtr->content[++ stackPtr->top] = x;
	return 0;
}

int8_t int_stack_top (const char_stack * const stackPtr){
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

char char_pop (char_stack * const stackPtr){
	if (char_isEmpty(stackPtr)){
		printf("DEBUG: stack underflow.");
		return -1;
	}
	int8_t result = stackPtr->content[stackPtr->top --];
	return result;
}

uint8_t char_push (char_stack * const stackPtr, char x){
	if (char_isOverflow(stackPtr)) {
		printf("DEBUG: stack overflow.");
		return 1;
	}
	stackPtr->content[++ stackPtr->top] = x;
	return 0;
}

char char_top (const char_stack * const stackPtr){
	return stackPtr->top;
}
