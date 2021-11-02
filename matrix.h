#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef float real;
typedef unsigned int uint;

typedef struct{
	uint rows, cols;
	real *data;
} matrix;

matrix *create_matrix(uint rows, uint cols, real inival);

matrix *add_matrix(matrix *m, matrix *n);

void free_matrix(matrix **m);

void print_matrix(matrix *m);

#endif