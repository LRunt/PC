#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
	stack *s = NULL;
	double x;
	char input[200] = "0";
	char znak;
	int i = 0; 
	
	scanf("%s", input);
	znak = input[i];
	
	while(znak != 0){
		i++;
		printf("%d", znak);
		znak = input[i];	
	}
	
	/*
	s = stack_create(10, sizeof(double));
	x = 5.0; stack_push(s, (void *) &x);
	x = 7.0; stack_push(s, (void *) &x);
	x = 9.0; stack_push(s, (void *) &x);
	
	while(stack_pop(s, &x)){
		printf("%lf\n", x);
	}*/
	
	
	
	stack_free(&s);
	
	return EXIT_SUCCESS;
}