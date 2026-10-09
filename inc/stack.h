#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdbool.h>

#define STACK_MAX_SIZE 128

/* In this project, the first procedure I'd like to use is: Seperated stack types for char and int.
 * Probably we'll have another approach to create a generical stack?
 * */

/* Stack for integer */

typedef struct {
	int8_t top;
	double content[STACK_MAX_SIZE];
} num_stack;

bool num_stack_isEmpty (const num_stack * const stackPtr);
bool num_stack_isOverflow (const num_stack * const stackPtr);
double num_stack_pop (num_stack * const stackPtr);
uint8_t num_stack_push (num_stack * const stackPtr, double x);
double num_stack_top (const num_stack * const stackPtr);

/* Stack for charactor) */
typedef struct {
	int8_t top;
	char content[STACK_MAX_SIZE];
} char_stack;

bool char_stack_isEmpty (const char_stack * const stackPtr);
bool char_stack_isOverflow (const char_stack * const stackPtr);
char char_stack_pop (char_stack * const stackPtr);
uint8_t char_stack_push (char_stack * const stackPtr, char x);
char char_stack_top (const char_stack * const stackPtr);

#endif
