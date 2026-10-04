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

uint8_t pop (stack * const stackPtr){
	if (isEmpty(stackPtr)){
		printf("DEBUG: stack underflow.");
		return -1;
	}
	uint8_t result = stackPtr->content[stackPtr->top --];
	return result;
}

uint8_t push (stack * const stackPtr, int8_t x){
	if (isOverflow(stackPtr)) return 1;
	stackPtr->content[++ stackPtr->top] = x;
	return 0;
}

int8_t top (const stack * const stackPtr){
	return stackPtr->top;
}
