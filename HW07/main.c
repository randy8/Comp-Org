#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

#include "char_out.h"
#include "print2505.h"

int main()
{
	// Some tests without conversion specifiers.
 	printf("\n%d\n", print2505(stdout, "Hello World!", NULL));
 	printf("\n%d\n", print2505(stdout, "Hello\twOrLd", NULL)); 

	// Example from the pdf document.
	uint8_t data[] = {0x01, 0x00, 0x00, 0x88, 0x00, 0x0a, 0x01, 0x00, 
				0x0b, 0x02, 0x20, 0x03, 0x01, 0x01, 0x02, 0x0b,
 				0x02, 0x01, 0x04, 0x01, 0x01, 0x02, 0x0c, 0x01,
				0x00, 0x07, 0x01, 0x01, 0x05, 0x01};

	print2505(stdout, "%% %1b, %1l, %2b, %2l, %4b, %4l, %8b, %8l\n", data);


	// Examples from the comments in print2505.h.
	uint8_t more[] = {0x00, 0x88, 0x00, 0x84};

	printf("\n%d\n", print2505(stdout, "Hello\tWorld %% %2l %2b", more));
	printf("\n%d\n", print2505(stdout, "Hello\tWorld %% %l2 %2b\n", more));

	return 0;
}
