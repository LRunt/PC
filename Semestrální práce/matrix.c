#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

matrix *create_matrix(uint cols, uint rows){
	matrix *new = NULL;
	
	/* sanity check*/
	if(!rows || !cols) return NULL;
	
	/* allocations */
	new = (matrix *) malloc(sizeof(matrix));
	if(!new) return NULL;
	
	new -> cols = cols;
	new -> rows = rows;
	new -> data = (uint *) malloc((rows * cols) * sizeof(uint));
	if(!new -> data){
		free(new);
		return NULL;
	}
	
	return new;
}

void print_matrix(matrix *m){
	int i, j;
	if(!m){
		printf("|X|\n");
		return;	
	} 
	
	for(i = 0; i < m -> rows; i++){
		for(j = 0; j < m -> cols; j++){
			printf("%02X ", m -> data[i * m -> cols + j]);
		}
		printf("\n");
	}
}

void free_matrix(matrix **m){
	if(!*m) return;
	free((*m)->data);
	free(*m);
	*m = NULL;
}