#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#include "factorial.h"

int main(int argc, char** argv) 
{
   printf("%21"PRIu64"\n", Factorial());
   printf("%21"PRIu64"\n", Factorial());
   printf("%21"PRIu64"\n", Factorial());
   printf("%21"PRIu64"\n", Factorial());
   printf("%21"PRIu64"\n", Factorial());

   return 0;
}

