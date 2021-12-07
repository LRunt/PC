#include <stdlib.h>
#include <stdio.h>
#include "node.h"

node *create_node(uint value){
	node *new = NULL;
	
	/*sanity check*/
	if(!value) return NULL;
	
	/* allocations */
	new = (node *) malloc(sizeof(node));
	if(!new) return NULL;
	
	new->value = value;
	new->next = -1;
	
	return new;
}