#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

matrix *create_matrix(uint rows, uint cols, real inival){
	uint i, rc;
	matrix *temp = NULL;
	
	/* sanity check */
	if(!cols || !cols) return NULL;
	
	/* allocations */
	temp = (matrix *) malloc(sizeof(matrix));
	if(!temp) return NULL;
	
	temp -> cols = cols;
	temp -> rows = rows;
	temp -> data = (real *) malloc((rc = rows * cols) * sizeof(real));
	if(!temp -> data){
		free(temp);
		return NULL;
	}
	
	/* initalization */
	for(i = 0; i < rc; i++) temp -> data[i] = inival;
		
	return temp;
}

matrix *add_matrix(matrix *m, matrix *n){
	int i, j;
	uint cols, rows;
	matrix *temp = NULL;
	if(!m || !n) return NULL;
	if((m -> rows != n -> rows) || (m -> cols != n -> cols)){
		printf("Matice nemaji stejny rozmer\n");
		return NULL;
	}
	
	temp = (matrix *) malloc(sizeof(matrix));
	if(!temp) return NULL;
	
	temp -> cols = m -> cols;
	temp -> rows = m -> rows;
	temp -> data = (real *) malloc(cols * rows * sizeof(real));
	if(!temp -> data){
		free(temp);
		printf("hehe");
		return NULL;
	}
	
	for(i = 0; i < temp -> rows; i++){
		for(j = 0; j < temp -> cols; j++){
			temp -> data[i * temp -> cols + j] = m -> data[i * temp -> cols + j] + n -> data[i * temp -> cols + j];
		}	
	}
	return temp;
}

void print_matrix(matrix *m){
	int i, j;
	if(!m){
		printf("|X|\n");
		return;	
	} 
	
	for(i = 0; i < m -> rows; i++){
		printf("|");
		for(j = 0; j < m -> cols; j++){
			printf("%.2lf ", m -> data[i * m -> cols + j]);
		}
		printf("|\n");
	}
}

void free_matrix(matrix **m){
	if(!*m) return;
	free((*m)->data);
	free(*m);
	*m = NULL;
}