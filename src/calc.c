#include "calc.h"
#include <stdio.h>

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
