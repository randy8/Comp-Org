#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "BinaryInt.h"

void printResult(FILE * Log, const uint8_t Result[], const uint8_t Left[], 
			const uint8_t Right[], bool no_overflow);

int main()
{
	bool overflow;
	uint8_t Result[NUM_BITS], Left[NUM_BITS], Right[NUM_BITS];
	
	printf("Use BI_Create to initializ Right to 42 and Left to -42.\n");
	BI_Create(Right, 42);
	BI_Create(Left, -42);

	printf("Use BI_Neg(Result, Left):  \n");
	BI_Neg(Result, Left);	
	BI_fprintf(stdout, Result,  "Result: ", "   ");
	fprintf(stdout, "%12"PRId32"\n", BI_ToDecimal(Result));
	printf("\n");

	printf("Use BI_Add(Result, Left, Right):  \n");
	overflow = BI_Add(Result, Left, Right);
	printResult(stdout, Result, Left, Right, overflow);
	printf("\n");

	printf("Use BI_Sub(Result, Left, Right):  \n");
	overflow = BI_Sub(Result, Left, Right);
	printResult(stdout, Result, Left, Right, overflow);
	printf("\n");

	return 0;
}



void printResult(FILE * Log, const uint8_t Result[], const uint8_t Left[], 
			const uint8_t Right[], bool no_overflow) 
{
	BI_fprintf(Log, Left,   "Left:   ", "   ");
	fprintf(Log, "%12"PRId32"\n", BI_ToDecimal(Left));

	BI_fprintf(Log, Right,  "Right:  ", "   ");
	fprintf(Log, "%12"PRId32"\n", BI_ToDecimal(Right));
	fprintf(Log, "        ---------------------------------------\n");
   
	if (no_overflow) 
	{
		BI_fprintf(Log, Result, "        ", "   ");
		fprintf(Log, "%12"PRId32"\n", BI_ToDecimal(Result));
	}
	else 
	{
		BI_fprintf(Log, Result, "        ", "   ");
		fprintf(Log, "%12"PRId32"\n", BI_ToDecimal(Result));
		fprintf(Log, "        overflow indicated\n");
	}
	fflush(Log);
}
