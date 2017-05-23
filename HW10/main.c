#include <stdio.h>
#include <stdint.h>

#include "bytes.h"


int main()
{
	bytes_t b, e;

	// Initialize a couple bytes_t variables.
	bytes_init(&b);
	bytes_init(&e);

	// Add the upper case alphabet twice to b:
	for (int x = 0; x < 52; x++)
	{
		uint8_t chr[] = {(x % 26) + 65};
		bytes_insert(&b, bytes_usage(&b), chr, 1);
	}
	// Add a null terminator at the end of b.
	bytes_insert(&b, bytes_usage(&b), (uint8_t *)"\0", 1);

	// Print b out like it's a string variable.
	printf("%s\n", bytes_data(&b));

	// Let's access b using the range function:

	// Start at index 0, moving up to (but not including) usage.
	// This will go to every other byte because step is 2.
	range_t r = {.start = 0, .stop = bytes_usage(&b), .step = 2};

	uint8_t * next = bytes_range(&b, &r);

	// Use result only after testing. 
	while (next != NULL)
	{
		// Print the byte as an uint8_t and a char.
		printf("%"PRIu8": \"%c\"\n", *next, *next);
		// Try to get the next byte.
		next = bytes_range(&b, &r);
	}	

	// Make a deep copy (not a reference or pointer) of b in c.
	bytes_t c;
	bytes_init(&c);

	if (bytes_copy(&c, &b))
	{
		// Erase something in c, b and c should print differently now.
		bytes_erase(&b, 0, 1);
		bytes_fprintf(stdout, &b);
		bytes_fprintf(stdout, &c);
	}
	
	// Let's do some stuff with bytes_t e.

	// You might see byte patterns like these in memory,  
	// or at the beginning of files:

	// 0xDEADBEEF is sometimes used to fill uninitialized memory, 
	// which can make reading memory dumps easier.
	uint8_t deaf_beef[] = {0xDE, 0xAD, 0xBE, 0xEF};

	// The first four bytes of a java .class file are 0xCAFEBABE.
	uint8_t cafe_babe[] = {0xCA, 0xFE, 0xBA, 0xBE};

	// 0x8BADFOOD is used in iOS crash reports.
	uint8_t ate_bad_food[] = {0x8B, 0xAD, 0xF0, 0x0D};

	// For more examples see: https://en.wikipedia.org/wiki/Hexspeak

	// Insert those byte patterns at the end of bytes_t e.
	bytes_insert(&e, bytes_usage(&e), deaf_beef, 4);	
	bytes_insert(&e, bytes_usage(&e), cafe_babe, 4);	
	bytes_insert(&e, bytes_usage(&e), ate_bad_food, 4);	

	bytes_fprintf(stdout, &e);
	

	// Iterate through e byte by byte.
	range_t byte_by_byte = {0, bytes_usage(&e), 1};
	next = bytes_range(&e, &byte_by_byte);

	// Holds the output/result from bytes_get.
	uint64_t out;

	while (next != NULL)
	{
		if (bytes_get(&e, next - bytes_data(&e), BITS8, LITTLE, &out))
		{
			printf("%02"PRIx64"\n", out);
		}

		if (bytes_get(&e, next - bytes_data(&e), BITS8, BIG, &out))
		{
			printf("%02"PRIx64"\n", out);
		}
	
		next = bytes_range(&e, &byte_by_byte);
	}

	// Iterate through e four bytes at a time.
	range_t four_bytes = {0, bytes_usage(&e), 4};
	next = bytes_range(&e, &four_bytes);

	while (next != NULL)
	{
		if (bytes_get(&e, next - bytes_data(&e), BITS32, LITTLE, &out))
		{
			printf("%08"PRIx64"\n", out);
		}

		if (bytes_get(&e, next - bytes_data(&e), BITS32, BIG, &out))
		{
			printf("%08"PRIx64"\n", out);
		}
	
		next = bytes_range(&e, &four_bytes);
	}


	// Try erase in a few different positions.
	bytes_erase(&e, 0, 1);
	bytes_fprintf(stdout, &e);

	bytes_erase(&e, bytes_usage(&e)/2, 2);
	bytes_fprintf(stdout, &e);


	bytes_erase(&e, bytes_usage(&e) - 1, 1);	
	bytes_fprintf(stdout, &e);

	bytes_erase(&e, bytes_usage(&e)/2, 10);
	bytes_fprintf(stdout, &e);


	// Potentially free the dynamic memory allocated for b, c, and e.
	bytes_free(&b);
	bytes_free(&c);
	bytes_free(&e);

	return 0;
}

