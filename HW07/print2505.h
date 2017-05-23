#ifndef PRINT2505_H
#define PRINT2505_H

#include <stdio.h>
#include <stdint.h>

// print2505() is our variant of the of the printf() function. 
//
// Like printf(), our function has a formatting string and conversion
// specifiers. Unlike printf(), the data or variables we're printing 
// reside in the array pointed to by the data parameter. Further, for
// simplicity our function will only print unsigned numbers.
//
// Pre:
// 	out    - Points to an already opened file stream.
//	format - Points to a C string containing formatting information
//	         and is not NULL.
//	data   - Points to array of uint8_t values or may be NULL when there
//	         are no conversion specifiers in the formatting string.
//
// Post:
//	The conversion specifiers and characters in the formatting string are
//	printed using the provided char_out() function. If an invalid 
//	conversion specifier is encountered then no more conversion specifiers 
//	or characters are processed or printed.
//
// Returns:
// 	The number of characters printed. If an invalid conversion specifier is 
// 	encountered then return -1.
//
// Restrictions:
//	-You may not use array brackets for this assignment. Any array
//	 accesses must use pointer arithmetic and the dereference operator.
// 	-You may NOT use I/O, e.g. any printf() or scanf() variants.
// 	-You may NOT use arrays, beyond the given parameters format and data.
//	-You may NOT use other libraries or built-in functions to convert to
//	 or from big or little endian format.
// 	-You may NOT use math.h or string.h, nor any function declared within.
// 	-Further, you MUST use the provided char_out() function to print the 
// 	 characters one at a time.
//
// Examples:
// 	Unless you encounter a conversion specifier, each character 
// 	should be printed as shown in the formatting string. Like printf(), 
// 	our conversion specifiers start with a %. The following examples
// 	without % characters would just print the given string literals:
//
//      // prints "Hello World!", returns 12
// 	print2505("Hello World!", NULL);
//
//	// prints "Hello	wOrLd", returns 11
// 	print2505("Hello\twOrLd", NULL); 
//
// 	When a % is encountered, we will normally examine the data parameter.
// 	print2505() conversion specifiers start with %, followed by a number
// 	(1, 2, 4, or 8 only), which is the number of bytes for the value we 
// 	are reading from *data, then a lower case 'b' or 'l' for big endian or 
// 	little endian. 
//
// 	The following are the valid conversion specifiers:
//		%1b, %1l, %2b, %2l, %4b, %4l, %8b, %8l
//
//      print2505() also supports "%%", a special case, which prints
// 	the literal %, and doesn't look at the data parameter.
//
//	The example below will read 2, 2 byte values from the array pointed
//	to by data, interpreting the first value in little endian byte ordering 
//	as 34816 (0x8800), and interpreting the the second in big endian byte 
//      ordering as 132 (0x0084).
//
//	uint8_t data[] = {0x00, 0x88, 0x00, 0x84};
//
//      // prints "Hello	World % 34816 132", returns 24
//	print2505("Hello\tWorld %% %2l %2b\n", data);
//
// 	If an invalid conversion specifier is encountered, i.e. "%l2", "% b", 
//	"%9l" you should stop processing the formatting string (and printing), 
//	and then return -1:
//
//      // prints "Hello	World % ", returns -1
//	print2505(stdout, "Hello\tWorld %% %l2 %2b\n", data);
//
int print2505(FILE *out, const char *format, const uint8_t *data);

#endif
