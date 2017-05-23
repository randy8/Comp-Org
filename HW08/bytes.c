#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#include "Untangle.h"

int main(int argc, char** argv) {

   // See if command line has correct number of tokens:
   if ( argc != 2 ) {
      printf("Invocation:  driver <name of binary input file>\n");
      exit(1);
   }

   // name of data file from which we will initialize the buffer
   char* genFileName = argv[1];   
   
   // pointer to in-memory buffer to pass to Untangle()
   uint8_t* Buffer = NULL;        

   // Create log file:
   FILE* Log = fopen("TestLog01.txt", "w");
   if ( Log == NULL ) {
      printf("Test driver encountered an error opening log file.\n");
      return 1;
   }
   // Open input file, if present:
   // "rb" for reading in binary mode
   FILE* binIn = fopen(genFileName, "rb");      
   if ( binIn == NULL ) {
      fprintf(Log, "Test driver encountered an error opening binary file.\n");
      return 2;
   }

   // Get size of input file:
   fseek(binIn, 0, SEEK_END);
   uint32_t fLength = ftell(binIn);
   // Create space in memory to hold file contents:
   Buffer = malloc(fLength);
  
   // Read contents of binary data file into buffer:
   fseek(binIn, 0, SEEK_SET);
   fread(Buffer, sizeof(char), (size_t)fLength, binIn);
   // Close input file:
   fclose(binIn);

   // Call Untangle() on in-memory buffer we just created:
   uint8_t wordsReported = Untangle(Buffer, Log);
   // Log the return value from Untange() to see if it's correct:
   fprintf(Log, "Words reported:  %"PRIu8"\n", wordsReported);
   
   // Close the log file:
   fclose(Log);
   // Exit:
   return 0;
}

