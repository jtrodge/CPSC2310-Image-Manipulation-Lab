/*
  Jason Rodgers
  CPSC 2311 Sp22 Section 01
  jtrodge@g.clemson.edu
*/

#include "functions.h"

// Run the program with the input file.
// Ex.) ./a.out input.txt
int main(int argc, char** argv) {
  // Special case for reading in command line arguments
  if (argc != 4) {
    printf("File will not open. argc < 4; ./a.out input.txt output.txt output2.txt\n");
    exit(1);
  }
  header_t* header;
  matrix Mat;
  matrix Mat3x3;
  matrix Mat5x5;
  header = readHeader(argv[1]);
  Mat = readMat(argv[1], header);
  Mat3x3 = copyMatrix(header, Mat);
  Mat5x5 = copyMatrix(header, Mat);
  printf("Original Matrix: \n");
  printOutput(header, Mat);
  filterMatrix3x3(header, Mat3x3, argv[2]);
  filterMatrix5x5(header, Mat5x5, argv[3]);
  freeMemory(Mat, header);
  freeMemory(Mat3x3, header);
  freeMemory(Mat5x5, header);


  return 0;
}
