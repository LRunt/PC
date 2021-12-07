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

int main(int argc, char *argv[]) {
	pgm *p = NULL;
	FILE *pgm_file;
	char version[3];
	int height;
	char *temp;
	
	//printf("%d\n", argc);
	
	/* check arguments */
	if(argc != 3){
		printf("Error: Missing argument!\nUsage: ccl.exe <input-file[.pgm]> <output-file>\n");
		return EXIT_FAILURE;
	}
	
	int len = strlen(argv[1]);
	//printf("%d\n", len);
	//printf("%c\n", *argv[1]);
	//printf("%c", *(argv[1] + len - 1));
	if(len < 5){
		addSuffix(argv[1]);
	}else{
		if(*(argv[1] + len - 1) != 'm' || *(argv[1] + len - 2) != 'g' || *(argv[1] + len - 3) != 'p' || *(argv[1] + len - 4) != '.'){
			addSuffix(argv[1]);
		}
		/*temp = (char *) malloc(sizeof(char) * len + sizeof(char) * 5);
			for(int i = 0; i < len; i++){
				*(temp + i) = *(argv[1] + i); 
			}
			*(temp + len) = '.';
			*(temp + len + 1) = 'p';
			*(temp + len + 2) = 'g';
			*(temp + len + 3) = 'm';
			*(temp + len + 4) = '\0';
			printf("%s", temp);*/
			//char suffix[5] = ".pgm";
		
			//strncat(argv[1], suffix, 5);
	}

	len = strlen(argv[2]);
		if(len < 5){
		addSuffix(argv[2]);
	}else{
		if(*(argv[2] + len - 1) != 'm' || *(argv[2] + len - 2) != 'g' || *(argv[2] + len - 3) != 'p' || *(argv[2] + len - 4) != '.'){
			addSuffix(argv[2]);
		}
	}	
	
	/*printf("\n");
	for(int i = 0; i < len; i++){
		printf("%c", *(argv[1] + i));
	}
	printf("\n");
	printf("%s\n", argv[1]);*/
	
	/*pgm_file = fopen(argv[1], "rb");
	if (pgm_file == NULL){
		printf("Cannot open file to read");
		return EXIT_FAILURE;
	} else{
		printf("vse v cajku");
	}*/

	
	
	//readData(argv[0], p);
	
	p = read_file(argv[1]);
	
	if(p == NULL){
		printf("Error: pgm struct doesnt exist!\n");
		return EXIT_FAILURE;
	}
	
	first_passage(p);
	
	//print_matrix(p->matrix); 
	
	//printf("%s\n", p->version);
	//printf("jdeme tisknout!");
	make_file(argv[2], p);
	
	return EXIT_SUCCESS;
}