#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"
#include "matrix.h"

/**
* Method read file and create new pgm struct
*/
pgm *read_file(const char *file_name){
	pgm *new;
	FILE *input = NULL;
	int i, j;
	uint number;
	
	/* sanity check*/
	if(!file_name)return NULL;
	
	/* memory allocation*/
	new = (pgm *) malloc(sizeof(pgm));
	if(!new){
		printf("Error: Memory allocation of pgm struct failed!\n");
		return NULL;
	} 
	
	input = fopen(file_name, "rb");
	
	/* sanity check*/
	if(input == NULL){
		printf("Error: File was not found!\n");
		return NULL;
	}
	
	fgets(new->version, sizeof(new->version), input);
	/* testing right format of pgm*/
	if(strcmp(new->version, "P5")){
		printf("Error: Wrong file type!\n");
		return NULL;
	}
	fscanf(input, "%d", &new->width);
	fscanf(input, "%d", &new->height);
    fscanf(input, "%d", &new->max);
    fgetc(input);
    
    if(!new->width || !new->height || !new->max){
    	printf("Error: file is corrupted!\n");
    	return NULL;
	}
    
    new->matrix = create_matrix(new->width, new->height);
	
	/* filling the matrix with data */
	for(i = 0; i < new->height; i++){
		for(j = 0; j < new->width; j++){
			number = fgetc(input);
			if(number != 0xFF && number != 0x00){
				printf("Error: Data isnt correct!\nPGM data must contains only values 0x00 and 0xFF!\n");
				return NULL;
			}
			new->matrix->data[i * new->width + j] = number;
			//printf("%d ", number);
		}
		//printf("\n");
	}
	
	//print_matrix(new->matrix);
	
	fclose(input);
		
	return new;
}

/**
* Method make file
*/
int make_file(const char *file_name, pgm *data){
	FILE *output = NULL;
	int i, j, number;
	
	/*sanity check */
	if(!file_name || !data) return EXIT_FAILURE;
	
	output = fopen(file_name, "wb");
	
	/* sanity check*/ 
	if(output == NULL){
		printf("Error: File wasn't created!\n");
		return EXIT_FAILURE;
	}
	
	fprintf(output, "%s\n", data->version);
	fprintf(output, "%d %d\n", data->width, data->height);
	fprintf(output, "%d\n", data->max);
	
	for(i = 0; i < data->height; i++){
		for(j = 0; j < data->width; j++){
			number = (data->matrix->data[i * data->width + j] * 0x30) % 0xFF;
			fputc(number, output);
		}
	}
	
	fclose(output);
	
	return EXIT_SUCCESS;
}

/**
* Method represents algorithm
*/
int first_passage(pgm *data){
	int *color_equivalence, value, new_value, old_value, *temp, i, j, k, num, coordinates, max_c = 10;
	uint number_of_colors = 0, a = 0x00;
	
	/* sanity check*/
	if(!data){
		printf("Error!");
		return EXIT_FAILURE;
	}  
	
	/* allocation */
	color_equivalence = (int *) calloc(max_c, sizeof(int));
	if(!color_equivalence) return EXIT_FAILURE;
	
	/*left upper corner*/
	if(data->matrix->data[0] != 0x00){
		number_of_colors++;
		color_equivalence[number_of_colors] = -1;
		data->matrix->data[0] = number_of_colors;
	}
	
	/** first row without top left corner*/
	for(i = 1; i < data->width; i++){
		if(data->matrix->data[i] != 0x00){
			if(data->matrix->data[i - 1] != 0x00){
				data->matrix->data[i] = data->matrix->data[i - 1];
			}else{
				number_of_colors++;
				/*Realocation */
				if(number_of_colors >= max_c){
					max_c *= 2;
					temp = (int*) realloc(color_equivalence, max_c * sizeof(int));
					if(!temp) return *color_equivalence;
					else color_equivalence = temp;	
				}  
				color_equivalence[number_of_colors] = -1;
				data->matrix->data[i] = number_of_colors;
			}
		}
	}
	
	/* Rest of data*/
	for(i = 1; i < data->height; i++){
		for(j = 0; j < data->width; j++){
			if(data->matrix->data[i * data->width + j] != 0x00){
				value = -1;
				if(j < data->width - 2){
					//i-1, j+1
					if(data->matrix->data[(i - 1) * data->width + j + 1] != 0x00){
						value = data->matrix->data[(i - 1) * data->width + j + 1];
					}
				}
				//i-1, j
				value = detect_colision(data, color_equivalence, value, (i - 1) * data->width + j, number_of_colors);
				if(j != 0){
					//i-1, j-1
					value = detect_colision(data, color_equivalence, value, (i - 1) * data->width + j - 1, number_of_colors);
					//i, j-1
					value = detect_colision(data, color_equivalence, value, i * data->width + j - 1, number_of_colors);
				}
				if(value != -1){
					//printf("%d ", value);
					data->matrix->data[i * data->width + j] = value;	                                
				}else{   
					number_of_colors++;
					/* Realocation */
					if(number_of_colors >= max_c){
						max_c *= 2;
						temp = (int*) realloc(color_equivalence, max_c * sizeof(int));
						if(!temp) return *color_equivalence;
						else color_equivalence = temp;	
					}  
					color_equivalence[number_of_colors] = -1;
					data->matrix->data[i * data->width + j] = number_of_colors;   	                                                          
				}
			}
		}
	}

	/* edit of field*/
	for(i = 1; i < number_of_colors; i++){
		num = i;
		while(color_equivalence[num] != -1){
			num = color_equivalence[num];
			color_equivalence[i] = num;
		}
	}
	
	/* Control (debug) printing */
/*	for(i = 0; i < number_of_colors; i++){
		printf("%d ", color_equivalence[i]);
	}
	int pocet = 0;
	for(i = 0; i < number_of_colors; i++){
		if(color_equivalence[i] == -1){
			pocet++;
		}
	}
	printf("\nPocet oblasti: %d\n",pocet); */
	
	/* second passage*/
	for(i = 0; i < data->height; i++){
		for(j = 0; j < data->width; j++){
			if(data->matrix->data[i * data->width + j] != 0x00){
				if(color_equivalence[data->matrix->data[i * data->width + j]] != -1){
					data->matrix->data[i * data->width + j] = color_equivalence[data->matrix->data[i * data->width + j]];
				}
			}                                                   
		}	  
	}
	
	free(color_equivalence);

	return EXIT_SUCCESS;
}

/**
* Method check conflicts in data
*/
int detect_colision(pgm *data, int *color_equivalence, int value, uint coordinates, uint number_of_colors){
	int new_value, old_value, i;
	
	/*sanity check*/
	if(!data || !color_equivalence){
		printf("Error!");
		return value;
	}
	
	/* check for collision */
	new_value = data->matrix->data[coordinates];
	if(new_value != 0x00){
		if(value != -1 && value != new_value){
			if(value < new_value){
				old_value = color_equivalence[new_value];
				if(color_equivalence[new_value] == -1 || color_equivalence[new_value] > value){
					color_equivalence[new_value] = value;
					if(old_value != -1){
						color_equivalence[old_value] = value;
					}
					for(i = 0; i < number_of_colors; i++){
						if(color_equivalence[i] == new_value){
							color_equivalence[i] = value;
						}	   
					}
					for(i = 0; i < number_of_colors; i++){
						if(color_equivalence[i] == old_value && old_value != -1){
							color_equivalence[i] = value;
						}   
					}
					return value;
				}else{		
					for(i = 0; i < number_of_colors; i++){
						if(color_equivalence[i] == new_value && old_value != -1){
							color_equivalence[i] = old_value;
						}	   
					}
					for(i = 0; i < number_of_colors; i++){
						if(color_equivalence[i] == value && old_value != -1){
							color_equivalence[i] = old_value;
						}   
					}
					return old_value;
				}
			}else{
				old_value = color_equivalence[value];
				if(color_equivalence[value] == -1 || color_equivalence[value] > new_value){
					color_equivalence[value] = new_value;
					for(i = 0; i < number_of_colors; i++){
						if(color_equivalence[i] == value){
							color_equivalence[i] = new_value;
						}	   
					}
					for(i = 0; i < number_of_colors; i++){
						if(color_equivalence[i] == old_value && old_value != -1){
							color_equivalence[i] = new_value;
						}
					}
					return new_value;
				}else{
					for(i = 0; i < number_of_colors; i++){
						if(color_equivalence[i] == new_value && old_value != -1){
							color_equivalence[i] = old_value;
						}	   
					}
					for(i = 0; i < number_of_colors; i++){
						if(color_equivalence[i] == value && old_value != -1){
							color_equivalence[i] = old_value;
						}	   
					}
					return old_value;
				}
			}
		}else{
			return new_value;
		}
	}else{
		return value;
	}
	return value;
}

/**
* Method free data
*/
void free_pgm(pgm **p){
	/* sanity check */
	if(!*p) return;
	
	free((*p)->matrix->data);
	free((*p)->matrix);
	(*p)->matrix = NULL;
	free(*p);
	*p = NULL;
}