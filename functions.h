#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <assert.h>

typedef int** MATRIX;

typedef struct header {
	int col;
	int row;
} header_t;

FILE* dataIn(char*, char*);
int** allocate(int**, header_t*);
int** calcNewMatrixThree(int**, header_t*);
FILE* printOut(MATRIX, FILE*, header_t*);
int** threeX(int**);
int** fiveX(int**);