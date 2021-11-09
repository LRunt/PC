#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

stack *stack_create(uint stack_size, uint item_size){
	stack *new;
	
	/* sanity check*/
	if (!stack_size || !item_size) return NULL;
	
	/*memory allocation */
	new = (stack *) malloc(sizeof(stack));
	if (!new) return NULL;
	
	new -> stack_size = stack_size;
	new -> item_size = item_size;
	new -> sp = -1;
	new -> data = (char *) malloc(stack_size * item_size);
	
	if(!new->data){
		free(new);
		return NULL;
	}
	
	return new;
}

int stack_push(stack *s, void *x){
	int i;
	if(!s || !x) return FAILURE;
	
	if(s -> sp < (int) s->stack_size - 1){
		s->sp++;
		for(i = 0; i < s->item_size; i++){
			s -> data[s -> sp * s -> item_size + i] = ((char *) x)[i];
		}
	} else return FAILURE;
	return SUCCESS;
}

int stack_pop(stack *s, void *x){
	int i;
	if(!s || !x) return FAILURE;
	
		if(s -> sp >= 0){
			for(i = 0; i < s->item_size; i++){
				((char *) x) [i] = s -> data[s -> sp * s -> item_size + i];
			}
		s->sp--;
	} else return FAILURE;
	
	return SUCCESS;
}

void stack_free(stack **s){
	if (!*s) return;
	
	free((*s)->data);
	free(*s);
	*s = NULL;
}