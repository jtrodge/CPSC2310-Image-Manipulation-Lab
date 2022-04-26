/*
  Jason Rodgers
  CPSC 2311 Sp22 Section 01
  jtrodge@g.clemson.edu
*/

#ifndef FILE_NAME_H
#define FILE_NAME_H

typedef int** matrix;
typedef struct Header{
  int width;
  int height;
} header_t;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

header_t* readHeader(char*);
matrix readMat(char*, header_t*);
void printOutput(header_t*, matrix);
matrix copyMatrix(header_t*, matrix);
int outputRange(int);
int sharpenCalc3x3(header_t*, matrix, int, int);
int sharpenCalc5x5(header_t*, matrix, int, int);
void filterMatrix3x3(header_t*, matrix, char*);
void filterMatrix5x5(header_t*, matrix, char*);
matrix allocateMemory(header_t*);
void freeMemory(matrix, header_t*);

#endif
