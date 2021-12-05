#ifndef	__PGM_H__
#define	__PGM_H__

#define	MIN_VALUE 0
#define	MAX_VALUE 255

//typedef unsigned int uint;

typedef struct{
	int width;
	int height;
	int max_value;
	int **matrix;
}pgm;

int **allocate_matrix(int width, int height);
void free_matrix(int **matrix, int width);
pgm* readData(const char *file_name, pgm *data);

#endif