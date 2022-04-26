/*
  Jason Rodgers
  CPSC 2311 Sp22 Section 01
  jtrodge@g.clemson.edu
*/

#include "functions.h"

// Run the program with the input file.
// Ex.) ./a.out input.txt
header_t* readHeader(char* str) {
  FILE* in = fopen(str, "r");
  header_t *read = (header_t*)malloc(256 * sizeof(header_t));
  // Reads header of file
  fscanf(in, "%d %d\n", &read->width, &read->height);
  return read;
}

matrix readMat(char* str, header_t* h) {
  FILE* in = fopen(str, "r");
  int tempW, tempH;
  fscanf(in, "%d%d", &tempW, &tempH);
  // Allocate Memory
  matrix Matrix = allocateMemory(h);
  // Store the values into 2d array
  for (int i = 0; i < h->width; i++) {
    for (int j = 0; j < h->height; j++) {
      fscanf(in, "%d", &Matrix[i][j]);
    }
    fscanf(in, "\n");
  }
  return Matrix;
  fclose(in);
}

void printOutput(header_t* h, matrix outputData) {
  // prints output in correct format
  for (int i = 0; i < h->width; i++) {
    for(int j = 0; j < h->height; j++) {
        printf("%d ", outputData[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

matrix copyMatrix(header_t* h, matrix original) {
  matrix newMatrix = allocateMemory(h);
  for (int i = 0; i < h->width; i++) {
    for (int j = 0; j < h->height; j++) {
      newMatrix[i][j] = original[i][j];
    }
  }
  return newMatrix;
}

// Checks to see if values are in range of 0-255
int outputRange(int val) {
    // if values is less than 0
    if (val < 0) {
      val = 0;
    }
    // if values is greater than 255
    else if (val > 255) {
      val = 255;
    }
    return val;
}

int sharpenCalc3x3(header_t* h, matrix Matrix, int i, int j) {
  // Filter values being used
  int sharp[3][3] = { {0, -1, 0},
                {-1, 5, -1},
                {0, -1, 0} };
  int result;
  if (i == 0 || j == 0 || i == (h->width - 1) || j == (h->height - 1)) { result = Matrix[i][j]; }
  else {
    // 1st row
    result = (Matrix[i-1][j-1])*(sharp[0][0]);
    result += (Matrix[i-1][j])*(sharp[0][1]);
    result += (Matrix[i-1][j+1])*(sharp[0][2]);
    // 2nd row
    result += (Matrix[i][j-1])*(sharp[1][0]);
    result += (Matrix[i][j])*(sharp[1][1]);
    result += (Matrix[i][j+1])*(sharp[1][2]);
    // 3rd row
    result += (Matrix[i+1][j-1])*(sharp[2][0]);
    result += (Matrix[i+1][j])*(sharp[2][1]);
    result += (Matrix[i+1][j+1])*(sharp[2][2]);
  }
  return outputRange(result);
}


int sharpenCalc5x5(header_t* h, matrix Matrix, int i, int j) {
  int result;
  if (i == 0 || i == 1 || j == 0 || j == 1
      || i == (h->width - 1) || i == (h->width - 2) || j == (h->height - 1) || j == (h->height - 2)) { result = Matrix[i][j]; }
  else {
    // 1st row
    result = (Matrix[i-2][j-2])*0;
    result += (Matrix[i-2][j-1])*0;
    result += (Matrix[i-2][j])*-1;
    result += (Matrix[i-2][j+1])*0;
    result += (Matrix[i-2][j+2])*0;
    // 2nd row
    result += (Matrix[i-1][j-2])*0;
    result += (Matrix[i-1][j-1])*0;
    result += (Matrix[i-1][j])*-1;
    result += (Matrix[i-1][j+1])*0;
    result += (Matrix[i-1][j+2])*0;
    // 3rd row
    result += (Matrix[i][j-2])*-1;
    result += (Matrix[i][j-1])*-1;
    result += (Matrix[i][j])*9;
    result += (Matrix[i][j+1])*-1;
    result += (Matrix[i][j+2])*-1;
    // 4th row
    result += (Matrix[i+1][j-2])*0;
    result += (Matrix[i+1][j-1])*0;
    result += (Matrix[i+1][j])*-1;
    result += (Matrix[i+1][j+1])*0;
    result += (Matrix[i+1][j+2])*0;
    // 5th row
    result += (Matrix[i+2][j-2])*0;
    result += (Matrix[i+2][j-1])*0;
    result += (Matrix[i+2][j])*-1;
    result += (Matrix[i+2][j+1])*0;
    result += (Matrix[i+2][j+2])*0;
  }
  return outputRange(result);
}


void filterMatrix3x3(header_t* h, matrix Matrix, char* str) {
  FILE* out = fopen(str, "w");
  matrix newMatrix = allocateMemory(h);
  for (int i = 0; i < h->width; i++) {
    for (int j = 0; j < h->height; j++) {
      newMatrix[i][j] = sharpenCalc3x3(h, Matrix, i, j);
    }
  }
  fprintf(out, "Filtered 3x3 Matrix: ");
  for (int i = 0; i < h->width; i++) {
    for (int j = 0; j < h->height; j++) {
      if (i == 0 || j == 0 || i == (h->width - 1) || j == (h->height - 1)) { continue; }
      fprintf(out, "%d ", newMatrix[i][j]);
    }
    fprintf(out, "\n");
  }
}

void filterMatrix5x5(header_t* h, matrix Matrix, char* str) {
  FILE* out = fopen(str, "w");
  matrix newMatrix = allocateMemory(h);
  for (int i = 0; i < h->width; i++) {
    for (int j = 0; j < h->height; j++) {
      newMatrix[i][j] = sharpenCalc5x5(h, Matrix, i, j);
    }
  }
  fprintf(out, "Filtered 5x5 Matrix: ");
  for (int i = 0; i < h->width; i++) {
    for (int j = 0; j < h->height; j++) {
      if (i == 0 || j == 0 || i == (h->width - 1) || j == (h->height - 1)) { continue; }
      fprintf(out, "%d ", newMatrix[i][j]);
    }
    fprintf(out, "\n");
  }
}

matrix allocateMemory(header_t* h) {
  // Allocates a 2d array
  matrix Matrix = (int**)malloc(h->width * sizeof(int*));
  for (int i = 0; i < h->width; i++) {
    Matrix[i] = (int*)malloc(h->height * sizeof(int));
  }
  return Matrix;
}

void freeMemory(matrix Matrix, header_t* h) {
  // Free the memory of the row, and then the rest of the contents
  for(int i = 0; i < h->width; i++) {
    free(Matrix[i]);
  }
  free(Matrix);
}
