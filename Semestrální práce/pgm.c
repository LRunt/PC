#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"
#include "matrix.h"
#include "node.h"

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
	if(!new) return NULL;
	
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
    new->matrix = create_matrix(new->width, new->height);
	
	/* filling the matrix with data */
	for(i = 0; i < new->height; i++){
		for(j = 0; j < new->width; j++){
			number = fgetc(input);
			if(number != 0xFF && number != 0x00){
				printf("Error: Data isnt correct!\n");
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

int first_passage(pgm *data){
	int *color_equivalence, value, new_value, old_value;
	uint number_of_colors = 0, a = 0x00;
	int i, j,k, num, coordinates, max_c = 10;
	
	//printf("%d", delka);
	/* sanity check*/
	if(!data){
		printf("Error!");
		return EXIT_FAILURE;
	} 
	
	//print_matrix(data->matrix); 
	
	/* allocation */
	color_equivalence = malloc(sizeof(node) * data->width * data->height);
	
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
				color_equivalence[number_of_colors] = -1;
				data->matrix->data[i] = number_of_colors;
			}
		}
	}
	
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
				if(data->matrix->data[(i - 1) * data->width + j] != 0x00){
					new_value = data->matrix->data[(i - 1) * data->width + j];
					old_value = color_equivalence[data->matrix->data[(i - 1) * data->width + j]];
					if(value != -1 && value != data->matrix->data[(i - 1) * data->width + j]){
						if(value < data->matrix->data[(i - 1) * data->width + j]){
							if(color_equivalence[data->matrix->data[(i - 1) * data->width + j]] == -1 || color_equivalence[data->matrix->data[(i - 1) * data->width + j]] > value){
								color_equivalence[data->matrix->data[(i - 1) * data->width + j]] = value;
								for(k = 0; k < number_of_colors; k++){
									if(color_equivalence[k] == new_value){
										color_equivalence[k] = value;
									}   
								}
								for(k = 0; k < number_of_colors; k++){
									if(color_equivalence[k] == old_value && old_value != -1){
										color_equivalence[k] = value;
									}   
								}
							}else{
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == new_value && old_value != -1){
											color_equivalence[k] = old_value;
										}	   
									}
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == value && old_value != -1){
											color_equivalence[k] = old_value;
										}   
									}
								} 
						}else{
							if(color_equivalence[value] == -1 || color_equivalence[value] > data->matrix->data[(i - 1) * data->width + j]){
								color_equivalence[value] = data->matrix->data[(i - 1) * data->width + j];
								for(k = 0; k < number_of_colors; k++){
									if(color_equivalence[k] == value){
										color_equivalence[k] = new_value;
									}	   
								}
							}
							value = data->matrix->data[(i - 1) * data->width + j];
						}
						//	
					}else{
						value = data->matrix->data[(i - 1) * data->width + j];
					}
				}
				if(j != 0){
					//i-1, j-1
					if(data->matrix->data[(i - 1) * data->width + j - 1] != 0x00){
						if(value != -1 && value != data->matrix->data[(i - 1) * data->width + j - 1]){
							new_value = data->matrix->data[(i - 1) * data->width + j - 1];
							old_value = color_equivalence[data->matrix->data[(i - 1) * data->width + j - 1]];
							if(value < data->matrix->data[(i - 1) * data->width + j - 1]){
								if(color_equivalence[data->matrix->data[(i - 1) * data->width + j - 1]] == -1 || color_equivalence[data->matrix->data[(i - 1) * data->width + j - 1]] > value){
									color_equivalence[data->matrix->data[(i - 1) * data->width + j - 1]] = value;
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == new_value){
											color_equivalence[k] = value;
										}	   
									}
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == old_value && old_value != -1){
											color_equivalence[k] = value;
										}   
									}
								}else{
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == new_value && old_value != -1){
											color_equivalence[k] = old_value;
										}	   
									}
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == value && old_value != -1){
											color_equivalence[k] = old_value;
										}   
									}
								}
							}else{
								if(color_equivalence[value] == -1 || color_equivalence[value] > data->matrix->data[(i - 1) * data->width + j - 1]){
									color_equivalence[value] = data->matrix->data[(i - 1) * data->width + j - 1];
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == value){
											color_equivalence[k] = new_value;
										}	   
									}
								}
								value = data->matrix->data[(i - 1) * data->width + j - 1];
							}
						}else{
							value = data->matrix->data[(i - 1) * data->width + j - 1];
						}
					}
					//i, j-1
					if(data->matrix->data[i * data->width + j - 1] != 0x00){
						if(value != -1 && value != data->matrix->data[i * data->width + j - 1]){
							new_value = data->matrix->data[i * data->width + j - 1];
							old_value = color_equivalence[data->matrix->data[i * data->width + j - 1]];
							if(value < data->matrix->data[i * data->width + j - 1]){
								if(color_equivalence[data->matrix->data[i * data->width + j - 1]] == -1 || color_equivalence[data->matrix->data[i * data->width + j - 1]] > value){
									color_equivalence[data->matrix->data[i * data->width + j - 1]] = value;
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == new_value){
											color_equivalence[k] = value;
										}	   
									}
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == old_value && old_value != -1){
											color_equivalence[k] = value;
										}   
									}
								}else{
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == new_value && old_value != -1){
											color_equivalence[k] = old_value;
										}	   
									}
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == value && old_value != -1){
											color_equivalence[k] = old_value;
										}   
									}
								}
							}else{
								if(color_equivalence[value] == -1 || color_equivalence[value] > data->matrix->data[i * data->width + j - 1]){
									color_equivalence[value] = data->matrix->data[i * data->width + j - 1];
									for(k = 0; k < number_of_colors; k++){
										if(color_equivalence[k] == value){
											color_equivalence[k] = new_value;
										}	   
									}
								}
								value = data->matrix->data[i * data->width + j - 1];
							}
						}else{
							value = data->matrix->data[i * data->width + j - 1];
						}
					}
				}
				if(value != -1){
					//printf("%d ", value);
					data->matrix->data[i * data->width + j] = value;	                                
				}else{   
					number_of_colors++;
					color_equivalence[number_of_colors] = -1;
					data->matrix->data[i * data->width + j] = number_of_colors;                                                                 
				}
			}
		}
	}
	
	for(i = 0; i < number_of_colors; i++){
		printf("%d ", color_equivalence[i]);
	}
	printf("\n");

	for(i = 1; i < number_of_colors; i++){
		num = i;
		while(color_equivalence[num] != -1){
			num = color_equivalence[num];
			color_equivalence[i] = num;
		}
	}
	
	for(i = 0; i < number_of_colors; i++){
		printf("%d ", color_equivalence[i]);
	}
	
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

	return EXIT_SUCCESS;
}

int second_passage(pgm *data){
	int i, j;
	
	/* sanity check*/
	if(!data){
		printf("Error!");
		return EXIT_FAILURE;
	} 
	
	for(i = 0; i < data->height; i++){
		for(j = 0; j < data->width; j++){
			if(data->matrix->data[i * data->width + j] != 0x00){
				
			}                                                   
}  }
	return EXIT_SUCCESS;
}