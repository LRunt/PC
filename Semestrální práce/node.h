#ifndef __NODE_H__
#define __NODE_H__

typedef unsigned int uint;

typedef struct{
	uint value, next;
}node;

node *create_node(uint value);

#endif