#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

int **allocate_matrix(int width, int height){
	int **return_value;
	int i;
	
	return_value = (int **)malloc(sizeof(int *) * width);
	if (return_value == NULL){
		printf("memory allocation failure");
		exit(EXIT_FAILURE);
	}
	
	for(i = 0; i < width; i++){
		return_value[i] = (int *)malloc(sizeof(int) * height);
		if(return_value[i] == NULL){
			printf("memory allocation failure");
			exit(EXIT_FAILURE);
		}
	}
	
	return return_value;
}

void free_matrix(int **matrix, int width){
	int i;
	
	for(i = 0; i < width; i++){
		free(matrix[i]);
	}
	free(matrix);
}

/* reading */
pgm* readData(const char *file_name, pgm *data){
	FILE *pgm_file;
	char version[3];
	int i, j;
	int lo, hi;
	
	/* sanity check*/
	if(!file_name || !data)return NULL;
	
	pgm_file = fopen(file_name, "rb");
	if (pgm_file == NULL){
		printf("Cannot open file to read");
		exit(EXIT_FAILURE);
	}
	fgets(version, sizeof(version), pgm_file);
    if (strcmp(version, "P5")) {
        fprintf(stderr, "Wrong file type!\n");
        exit(EXIT_FAILURE);
	}
    fscanf(pgm_file, "%d", &data->height);
    fscanf(pgm_file, "%d", &data->width);
    fscanf(pgm_file, "%d", &data->max_value);
    fgetc(pgm_file);
 
    data->matrix = allocate_matrix(data->width, data->height);
    if (data->max_value > 255) {
        for (i = 0; i < data->width; ++i) {
            for (j = 0; j < data->height; ++j) {
                hi = fgetc(pgm_file);
                lo = fgetc(pgm_file);
                data->matrix[i][j] = (hi << 8) + lo;
            }
        }
    }
    else {
        for (i = 0; i < data->width; ++i) {
            for (j = 0; j < data->height; ++j) {
                lo = fgetc(pgm_file);
                data->matrix[i][j] = lo;
            }
        }
    }
 
    fclose(pgm_file);
    return data;
}