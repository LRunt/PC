#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

int main(int argc, char *argv[]) {
	pgm *p = NULL;
	FILE *pgm_file;
	char version[3];
	int height;
	char *temp;
	
	printf("%d\n", argc);
	
	if(argc != 3){
		printf("Error: Missing argument!\nUsage: ccl.exe <input-file[.pgm]> <output-file>");
		return EXIT_FAILURE;
	}
	
	int len = strlen(argv[1]);
	//printf("%d\n", len);
	//printf("%c\n", *argv[1]);
	//printf("%c", *(argv[1] + len - 1));
	if(*(argv[1] + len - 1) == 'm' && *(argv[1] + len - 2) == 'g' && *(argv[1] + len - 3) == 'p' && *(argv[1] + len - 4) == '.'){
		printf("true");
	}else{
		temp = (char *) malloc(sizeof(char) * len + sizeof(char) * 5);
		for(int i = 0; i < len; i++){
			*(temp + i) = *(argv[1] + i); 
		}
		*(temp + len) = '.';
		*(temp + len + 1) = 'p';
		*(temp + len + 2) = 'g';
		*(temp + len + 3) = 'm';
		*(temp + len + 4) = '\0';
		printf("%s", temp);
	}
	len = strlen(argv[1]);	
	
	printf("\n");
	for(int i = 0; i < len; i++){
		printf("%c", *(argv[1] + i));
	}
	printf("\n");
	printf("%s", argv[1]);
	
	/*pgm_file = fopen(argv[1], "rb");
	if (pgm_file == NULL){
		printf("Cannot open file to read");
		return EXIT_FAILURE;
	} else{
		printf("vse v cajku");
	}*/

	
	
	//readData(argv[0], p);
	
	return EXIT_SUCCESS;
}