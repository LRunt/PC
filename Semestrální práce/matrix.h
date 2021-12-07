#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef unsigned int uint;

typedef struct{
	uint rows, cols, *data;
}matrix;

matrix *create_matrix(uint cols, uint rows);
void print_matrix(matrix *m);

#endif