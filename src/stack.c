#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

bool int_stack_isEmpty (const int_stack * const stackPtr) {
	if (stackPtr->top == -1) return true;
	return false;
}

bool int_stack_isOverflow (const int_stack * const stackPtr){
	if (stackPtr->top == STACK_MAX_SIZE-1) return true;
	return false;
}

int32_t int_stack_pop (int_stack * const stackPtr){
	if (int_stack_isEmpty(stackPtr)){
		printf("DEBUG: stack underflow.");
		return -1;
	}
	int32_t result = stackPtr->content[stackPtr->top --];
	return result;
}

uint8_t int_stack_push (int_stack * const stackPtr, int32_t x){
	if (int_stack_isOverflow(stackPtr)) {
		printf("DEBUG: stack overflow.");
		return 1;
	}
	stackPtr->content[++ stackPtr->top] = x;
	return 0;
}

int32_t int_stack_top (const int_stack * const stackPtr){
	return stackPtr->top;

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
		printf("DEBUG: stack underflow.");
		return -1;
	}
	int8_t result = stackPtr->content[stackPtr->top --];
	return result;
}

uint8_t char_stack_push (char_stack * const stackPtr, char x){
	if (char_stack_isOverflow(stackPtr)) {
		printf("DEBUG: stack overflow.");
		return 1;
	}
	stackPtr->content[++ stackPtr->top] = x;
	return 0;
}

char char_stack_top (const char_stack * const stackPtr){
	return stackPtr->top;
}
