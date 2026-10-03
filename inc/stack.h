#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdbool.h>

#define STACK_MAX_SIZE 256

typedef struct {
	int8_t top;
	int8_t content[STACK_MAX_SIZE];
} stack;

bool isEmpty (const stack * const stackPtr);
bool isOverflow (const stack * const stackPtr);

#endif
