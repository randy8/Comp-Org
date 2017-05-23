#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "string_type.h"
#include "txtfile.h"


int main(int argc, char ** argv)
{
	size_t num_lines;
	string_t *lines = NULL;

	if (argc != 2)
	{
		printf("Must supply a filename on the command line.\n");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("Coudn't open file %s.\n", argv[1]);
		return 2;
	}

	// Try to read the file line by line.
	if (!txtfile_readlines(fp, &lines, &num_lines))
	{
		printf("Error reading lines from text file %s\n", argv[1]);
		return 3;
	}
	fclose(fp);

	printf("Find duplicate words in file %s:\n", argv[1]);

	// This is our previous word, starts out as the empty string.
	string_t prev;
	string_init(&prev);

	for (size_t l = 0; l < num_lines; l++)
	{
		size_t num_words; 
		string_t *words = NULL;
		size_t ln = l + 1;

		// Try to split up the line into words.
		if(!string_split(&words, &lines[l], " \t", &num_words))
		{
			printf("Error spliting line %zu", ln);
			break;
		}

		// Examine each word in the line.
		for (size_t w = 0; w < num_words; w++)
		{
			// Test with the previous word, if it's equal to
			// the current word, we've found a duplicate.
			if (strcmp(string_c_str(&prev), 
				string_c_str(&words[w])) == 0)
			{
				printf("\tDuplicate word %s on line %zu\n",
					string_c_str(&words[w]), ln);
			}

			// Current word becomes the previous word.
			if (!string_copy(&prev, &words[w]))
			{
				printf("Error copying word on line %zu\n", ln);
			 	break;
			}
		}

		// We're done with the result of the split, so deallocate.
		string_free_split(words, num_words);

	}

	printf("Print all of the lines, they should be unchanged:\n");
	for (size_t l = 0; l < num_lines; l++)
	{
		printf("\t%s\n", string_c_str(&lines[l]));
	}
	
	string_t joined;
	string_init(&joined);

	// Join the lines in the file with the separator CS2505	
	if(string_join(&joined, lines, num_lines, "CS2505"))
	{
		printf("Join the file lines with 'CS2505': \n");
		printf("'%s'\n", string_c_str(&joined));
	}

	
	printf("Try to erase 1000 from joined string: \n");
	string_erase(&joined, 10, 1000);

	printf("Erase the rest of the character from the end one by one: \n");
	while (!string_empty(&joined))
	{
		string_erase(&joined, string_len(&joined) - 1, 1);
		printf("'%s'\n", string_c_str(&joined));
	}

	// Some clean up, deallocate lines, joined, and prev.
	string_free_split(lines, num_lines);
	string_free(&joined);
	string_free(&prev);

	return 0;
}
