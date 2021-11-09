#ifndef __STACK_H__
#define __STACK_H__

#define SUCCESS 1
#define FAILURE 0

typedef unsigned int uint;

typedef struct{
	uint stack_size;
	uint item_size;
	int sp;
	char *data;
} stack;

stack *stack_create(uint stack_size, uint item_size);
int stack_push(stack *s, void *x);
int stack_pop(stack *s, void *x);
void stack_free(stack **s);

#endif