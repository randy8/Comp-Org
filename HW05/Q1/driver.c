// minimalist test driver for bigMesa.c
//
// Compile:  gcc -o driver -std=c99 -Wall driver.c bigMesa.c
//
// Execute:  ./driver -prof to generate new test data
//           ./driver       to repeat with last test data
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "bigMesa.h"

void initBuffer(int buffer[], int bufferSz);
void initArray(int A[], int A_Sz);
void writeArray(FILE* Out, int A[], int A_Sz);

// externally-linkable variables that bigMesa() can use to report results
int mesaMass  = 0;
int mesaStart = 0;
int mesaEnd   = 0;

int main(int argc, char** argv) {
   
   unsigned int seed = 0;
   FILE* Out = NULL;
   
   // Check for command-line argument to select random/repeat mode.
   if ( argc > 1 ) {
      seed = time(NULL);
      FILE* fp = fopen("seed.txt", "w");
      fprintf(fp, "%u\n", seed);
      fclose(fp);
      Out  = fopen("profResults.txt", "w");
   }
   else {
      FILE* fp = fopen("seed.txt", "r");
      fscanf(fp, "%u", &seed);
      fclose(fp);
      Out  = fopen("Results.txt", "w");
   }

   // Seed the random generator for test data creation.
   srand(seed);
   
   // The test code uses dynamic allocation, which we are about to cover.
   // Pick array size between 25 and 50.
   int  A_Sz = 25 + rand() % 26;
   // I'm embedding the array your function will work with inside a larger
   // array; paddingSz is the number of cells before and after the actual
   // data array.
   int  paddingSz = 100;
   // bufferSz is the size of the entire memory allocation.
   int  bufferSz = A_Sz + 2 * paddingSz;
   // Allocate a memory block dynamically:
   int* buffer = malloc( bufferSz * sizeof(int) );
   // Write dummy values into the entire memory block:
   initBuffer(buffer, bufferSz);
   // A marks the beginning of the array your function will see:
   int* A = buffer + paddingSz;
   
   // Write random data into the array your function will see:
   initArray(A, A_Sz);
   // Log the array contents:
   writeArray(Out, A, A_Sz);
   // Call your function:
   bigMesa(A, A_Sz);
   
   // Log the results:
   fprintf(Out, "\n");
   fprintf(Out, "%3d %3d %8d\n", mesaStart, mesaEnd, mesaMass);
   fprintf(Out, "\n");
   
   // Deallocate the memory block:
   free(buffer);
   
   fclose(Out);
   return 0;
}

/**
 *   Writes the same, random, filler value to the entire memory buffer.
 *   This is useful for looking for overruns writing values beyond the
 *   end of the embedded array, and somewhat less useful for detecting
 *   reads beyond the end of the embedded array.
 * 
 *   Pre:  buffer[] is of dimension bufferSz
 *   Post: buffer[0:bufferSz - 1] == fillValue 
 */
void initBuffer(int buffer[], int bufferSz) {

   int fillValue = 5000 + rand() % 1000;
   for (int pos = 0; pos < bufferSz; pos++) {
      buffer[pos] = fillValue;
   }   
}

/**
 *   Writes randomly-generated values into the test array.  The values are
 *   selected with some attention to generating "mesas".
 * 
 *   Pre:  A[] is of dimension A_Sz
 *   Post: A[0:A_Sz - 1] have been initialized
 */
void initArray(int A[], int A_Sz) {
   
   int pos = 0;
   while ( pos < A_Sz ) {
      
      A[pos] = rand() % 100;
      while ( pos + 1 < A_Sz && rand() % 4 > 0 ) {
         A[pos + 1] = A[pos];
         pos++;
      }
      pos++;
   }
}

/**
 *   Writes the elements of the test array to a specified file stream,
 *   including an indication of array indices.
 * 
 *   Pre:  Out is opened for writing to a file
 *         A[] contains A_Sz values
 *   Post: A[0:A_Sz = 1] have been written as described
 */
void writeArray(FILE* Out, int A[], int A_Sz) {
   
   for (int pos = 0; pos < A_Sz; pos++) {
      fprintf(Out, "%3d", pos);
   }
   fprintf(Out, "\n");
   for (int pos = 0; pos < A_Sz; pos++) {
      fprintf(Out, "%3d", A[pos]);
   }
   fprintf(Out, "\n");
}
