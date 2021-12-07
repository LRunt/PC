#ifndef	__PGM_H__
#define	__PGM_H__

#include "matrix.h"
#define	MIN_VALUE 0
#define	MAX_VALUE 255

typedef unsigned int uint;

typedef struct{
	char version[3];
	uint width, height, max;
	matrix *matrix;
}pgm;

pgm *read_file(const char *file_name);
int make_file(const char *file_name, pgm *data);
int first_passage(pgm *data);
int second_passage(pgm *data);

#endif