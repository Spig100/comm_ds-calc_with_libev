#include "calc.h"
#include "stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <ev.h>

double add (double x, double y){
	return x + y;
}

double substract (double x, double y){
	return x - y;
}

double multiply (double x, double y){
	return x * y;
}

double divide (double x, double y){
	if (y == 0) return NAN;
	return x / y;
}

Operation get_operation (char opr){
	switch(opr){
		case '+':
			return add;
			break;
		case '-':
			return substract;
			break;
		case '*':
			return multiply;
			break;
		case '/':
			return divide;
			break;
		default:
			return NULL;
			break;
	}
}

static void calc_cb (EV_P_ ev_io *w, int revents){
	char_stack operator;
	int_stack operand;
	if (revents & EV_READ){
		char ch;
		bool isMD = false;
		while (read(w->fd, &ch, 1) > 0){
			switch(ch){
				case '+':
				case '-':
					break;
				case '*':
				case '/':
					isMD = true;
					
					break;
				case ' ':
					break;
				default:
					break;
					
			}
		}
	}
}
