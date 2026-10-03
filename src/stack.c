#include "stack.h"
#include <stdbool.h>

bool isEmpty (const stack * const stackPtr) {
	if (stackPtr->top == -1) return true;
	return false;
}

bool isOverflow (const stack * const stackPtr){
	if (stackPtr->top == STACK_MAX_SIZE-1) return true;
	return false;
}
