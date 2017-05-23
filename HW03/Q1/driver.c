#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#include "duplicate_digits.h"

void test_duplicate();

int main(int argc, char** argv) 
{

   test_duplicate();
   
   return 0;
}

void test_duplicate() 
{

   // You can hardwire values (below and recompile) to test your solution.
   uint64_t Value = 12345;
   uint8_t  N     =     2;

   uint64_t Result = duplicate_digits(Value, N);

   printf("%21"PRIu64"%3"PRIu8"%21"PRIu64"\n", Value, N, Result);

}
