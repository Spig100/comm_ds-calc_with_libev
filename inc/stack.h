#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdbool.h>

#define STACK_MAX_SIZE 256

/* In this project, the first procedure I'd like to use is: Seperated stack types for char and int.
 * Probably we'll have another approach to create a generical stack?
 * */

/* Stack for integer */

typedef struct {
	int8_t top;
	int8_t content[STACK_MAX_SIZE];
} int_stack;

bool int_isEmpty (const int_stack * const stackPtr);
bool int_isOverflow (const int_stack * const stackPtr);
int8_t int_pop (int_stack * const stackPtr);
uint8_t int_push (int_stack * const stackPtr, int8_t x);
int8_t int_top (const int_stack * const stackPtr);

/* Stack for charactor) */
typedef struct {
	int8_t top;
	char content[STACK_MAX_SIZE];
} char_stack;

bool char_isEmpty (const char_stack * const stackPtr);
bool char_isOverflow (const char_stack * const stackPtr);
char char_pop (char_stack * const stackPtr);
uint8_t char_push (char_stack * const stackPtr, char x);
char char_top (const char_stack * const stackPtr);

#endif
