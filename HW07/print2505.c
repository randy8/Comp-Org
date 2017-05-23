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
// was obtained from an allowed source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// Randy Liang <randy8>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "char_out.h"
#include "print2505.h"

int print2505(FILE * out, const char *format, const uint8_t * data) {
    int char_count = 0;

    while (*format) { 
		char form = *format;
		if (form == '%') {
			long long accum = 0;
			int count = 1;
			*format++;
			char form = *format;
			int num = 0;
			char type = '\0'; // NULL pointer

			while (form == '%' || form == 'b' || form == 'l' // ensures cases are checked
				|| (form >= '0' && form <= '9')) { 
				if (form == '%') {
					char_out(out, form);
					char_count++;
				} 
				else if (count == 1) {
					if (form >= '0' && form <= '9') {
						num = (int) form - 48;
					} else {
					char_out(out, form);
					char_count++;
					}
				} 
				else if (count == 2) {
					if (form == 'b' || form == 'l') {
						type = form;
					} 
					else {
						char_out(out, form);
						char_count++;
					}
				}
				count++;
				*format++;
				form = *format;
			}
			*format--;

			if (type == 'l') {
				for (int i = 0; i < num; i++) {
					long long multiplier = 1;
					for (int j = 0; j < i; j++) {
					multiplier *= 256;
					}
					accum += *data * multiplier;
					*data++;
				}
				int *charcount = &char_count;
				convert(out, accum, charcount);
			} 
			else if (type == 'b') {
				for (int i = 0; i < num - 1; i++) {
					*data++;
				}
				for (int i = 0; i < num; i++) {
					long long multiplier = 1;
					for (int j = 0; j < i; j++) {
						multiplier *= 256;
					}
					accum += (*data) * multiplier;
					*data--;
				}
				for (int i = 0; i < num + 1; i++) {
					*data++;
				}
					int *charcount = &char_count;
					convert(out, accum, charcount);
				}
			} 
			else {
			    char_out(out, *format);
			    char_count++;
			}
		format++;
    }
    return char_count;
}

void convert(FILE *out, long long accum, int *char_count)
{
    int val = accum % 10; 
    char conv = val + '0'; //adding a char of 0 to an int converts the type

    if (accum > 10) {
		convert(out, accum / 10, char_count); //if accum is too big (can only have 0-9)
		char_out(out, conv);
		(*char_count)++;
    } 
    else {
		char_out(out, conv);
		(*char_count)++;
    }
}
