// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// or any other unauthorized source, either modified or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from another source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Curator System.
//
// Randy Liang <randy8>
#include "txtfile.h"

bool txtfile_read(FILE *in, string_t * const result)
{
	int size = LINE_CHUNK;
	char * temp = malloc(size);
	while (fgets(temp, size, (FILE*)in) != NULL)
	{
		if (temp == NULL)
		{
			return false;
		}
		int l = strlen(temp);
		bool res = string_insert(result, result->len, temp, l);
		bytes_fprintf(stdout, (&(result)->bytes));
		free(temp);
		temp = malloc(size);
	}
	return true;
}

bool txtfile_readlines(FILE *in, string_t ** const result, size_t * num_lines)
{
	string_t temp;
	string_init(&temp);
	txtfile_read(in, &temp);
	return string_split(result, &temp, "\n", num_lines);
}
