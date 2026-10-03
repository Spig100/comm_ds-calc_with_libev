#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 64


/* Structure Description -- Stack:
 * -----------------------------------------------------------------
 * A stack is a simple data structure with single accessable end.
 *
 * This stucture has some simple function:
 * - Pop:	Take the top element out and delete the top element.
 * - Push:	Push a new element on the top.
 * */

typedef struct {
	uint8_t top;
	int4_t array[MAX_SIZE];
} stack;


bool isEmpty(const stack * const stackPtr);

bool isOverflow(const stack * const stackPtr);
