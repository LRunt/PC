#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

/**
* Method adds suffix .pgm to name of file
*/
int addSuffix(char *prefix){
	char suffix[5] = ".pgm";
	
	strncat(prefix, suffix, 5);
	
	return EXIT_SUCCESS;
}

/**
* Main method
*/
int main(int argc, char *argv[]) {
	pgm *p = NULL;
	FILE *pgm_file;
	char version[3];
	int height;
	char *temp;
	
	/* check arguments */
	if(argc != 3){
		printf("Error: Missing argument!\nUsage: ccl.exe <input-file[.pgm]> <output-file>\n");
		return EXIT_FAILURE;
	}
	
	int len = strlen(argv[1]);
	
	/* Testing if first argument contains .pgm*/
	if(len < 5){
		addSuffix(argv[1]);
	}else{
		if(*(argv[1] + len - 1) != 'm' || *(argv[1] + len - 2) != 'g' || *(argv[1] + len - 3) != 'p' || *(argv[1] + len - 4) != '.'){
			addSuffix(argv[1]);
		}
	}

	/* Testing if second argument contains .pgm*/
	len = strlen(argv[2]);
		if(len < 5){
		addSuffix(argv[2]);
	}else{
		if(*(argv[2] + len - 1) != 'm' || *(argv[2] + len - 2) != 'g' || *(argv[2] + len - 3) != 'p' || *(argv[2] + len - 4) != '.'){
			addSuffix(argv[2]);
		}
	}	
	printf("\n");
	
	/* rading a pgm file*/
	p = read_file(argv[1]);
	
	if(p == NULL){
		printf("Error: PGM struct wasn't created!\n");
		return EXIT_FAILURE;
	}
	
	/* algorithm of coloring of labels*/
	first_passage(p);
	
	/* making of pgm file */
	make_file(argv[2], p);
	
	/* free data*/
	free_pgm(&p);
	
	return EXIT_SUCCESS;
}