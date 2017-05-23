#ifndef STRING_TYPE_H
#define STRING_TYPE_H

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "bytes.h"

// The string type, represents a more flexible string than a C string.
struct string_t
{
	// We can use our bytes_t type from before to store the characters 
	// and to help with most of the basic operations.
	bytes_t bytes;

	// We'll keep our own string len rather than just using bytes_usage().
	size_t len;
};

typedef struct string_t string_t;

// Instructor provided functions:

// Initializes a string_t variable.
// 
// Pre:
// 	str - Points to a valid string_t variable and is not NULL.
// 
// Post:
//	bytes - Has been initialized using bytes_init, and a null 
//	terminator has been added to make it an empty string.
//	len - Is initialized to 0.
//
void string_init(string_t * const str);


// Deallocates any dynamic memory allocated for *str.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Post:
// 	Frees any dynamically allocated memory for the bytes variable 
//	using bytes_free().
//
void string_free(string_t * const str);


// Status functions, these are one-liners:

// Is *str empty?
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Returns:
//	Returns true if str->len is 0, false otherwise.
//
bool string_empty(const string_t * const str);


// Accessor function, gets the len of the string_t, str->len.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Returns:
//	Returns str->len.
//
size_t string_len(const string_t * const str);


// Accessor function, gets the raw uint8_t pointer via bytes_data().
// We'll treat bytes_data(&str->bytes) like a char *, which is what we'd want 
// for a string type (and is what the function returns.)
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Returns:
//	Returns bytes_data(&str->bytes).
//
char * string_c_str(const string_t * const str);


// More complex functions that provide common operations for the string_t type:

// Sets one character in the string_t variable.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Post:
//	If index < str->len, then the character at that index has 
//	been set to the char, in.
//
// Returns:
//	If the character at index was set (i.e. index < str->len) the 
//	function will return true, false otherwise.
//
bool string_set(string_t * const str, size_t index, char in);


// Gets one character in the string_t variable.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Post:
//	If index < str->len, then the character at that index is 
//	stored into the target of the char*, out.
//
// Returns:
//	If the function could get the character at index (so index < str->len)
//	it will return true, false otherwise.
//
bool string_get(const string_t * const str, size_t index, char * const out);


// Inserts up to len characters, stored in the memory pointed to by buf, into 
// *str starting at the specified index.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//	buf - Points to a C string of up to len characters long. It may be 
//	shorter (stop when you find a null terminator and don't include it) 
//	or it may not be null terminated (just insert len characters).
//
// Post:
//	Up to len characters in buf are inserted into *str starting at index.
//	Ensure your internal string data is still null terminated.
//
// Returns:
//	If a required dynamic allocation fails (i.e. with bytes_insert()), or 
//	if index > str->len the function will return false, true otherwise.
//
// Other thoughts:
//	You are going to insert "before" index. So if you insert at index = 0 
//	you are inserting before the first character. Further, if you were to 
//	insert at index = str->len, it's like appending the characters at 
//	the end.
//
bool string_insert(string_t * const str, size_t index, 
			const char * const buf, size_t len);


// Erases up to len characters from *str starting at the specified index.
//
// Pre:
//	str - Points to a valid string_t variable and is not NULL.
//
// Post:
//	If index < str->len, then up to len characters have been erased from
//	*str starting at index. When index + len > str->len less than
//	len characters will be erased.
//
//	Ensure your internal string data is still null terminated. Do
//	not erase the null terminator, no matter how characters are erased.
//
// Returns:
//	If index >= str->len, then no erasure occurs and the function
//	returns false, true otherwise.
// 
bool string_erase(string_t * const str, size_t index, size_t len);


// Splits the string_t up into several sub string_t variables using the 
// characters in split as the delimiters. I'd recommend looking into strtok().
//
// Pre:
// 	str - Points to a valid string_t variable and is not NULL.
//	split - Is a C string containing the delimiters used to break up 
//	the string_t. 
//	result - Points to an uninitialized or NULL string_t * variable.
//
//  Post:
//	*result points to a dynamically allocated array of string_t 
//	variables, for example here we split by the characters " \t\n": 
//
// 		"Hello World" --> {"Hello", "World"}
//		"Hello  \tWorld  " --> {"Hello", "World"}
//		"CS2505 Fall\t2015\n" -->{"CS2505", "Fall", "2015"}
//
//	*num_splits should be set to the number of items stored in the 
//	new array *result.
//
//	You should not assume num_splits has been initialized prior to calling 
//	string_split().
//
//	Remember each of the resulting strings above is a string_t, so len 
//	and bytes should be set to appropriate values. For example, if 
// 	your array of string_t variables was called result, and you were 
//	spliting a string_t containing "Hello World" like above, result 
//	would look like: 
//
//	result[0].bytes = {.dlft="Hello", .data=NULL, .usage=6, .dim=16}
//	result[0].len = 5
//
//	result[1].bytes = {.dflt="World", .data=NULL, .usage=6, .dim=16}
//	result[1].len = 5
//
//	If the words were longer, i.e. len + 1 > DEFAULT_SIZE, bytes.data 
//	would hold the string, instead of bytes.dflt.
//      
//	A string_t with only delimiters (whitespace in this example) should 
//	return false, set *result to NULL and num_splits = 0.
//
//	Further, *str should be not be modified by this function! strtok()
//	will modify the original string so be sure to make a copy!
//
// Returns:
//	If dynamic allocation fails or the case mentioned above 
//	occurs (a string_t with only delimiters) this function will 
//	return false, true otherwise.
//
bool string_split(string_t ** const result, const string_t * const str, 
			const char * const split, size_t * num_splits);


// Free an array produced by the string_split() function.
//
// Pre:
//	words - Points to an array of string_t variables and is not NULL. The
//	array should have num_words elements.
//
// Post:
//	The dynamic memory for each string_t in the array and the array itself
//	have been deallocated.
//
//
void string_free_split(string_t * words, const size_t num_words);

// The reverse of the split function, this function joins an array of 
// string_t variables together using sep as the "glue".
//
// Pre:
// 	result - Points to a valid string_t variable and is not NULL.
//	words - Points to an array of string_t variables and is not NULL. The
//	array should have num_words elements.
//	sep - Is a C string containing the characters that will go between
//	the string_t variables in the *result.
//
// Example:
// 		{"Hello", "World"} with sep = " " --> "Hello World"
// 		{"Hello", "World"} with sep = "\t" --> "Hello\tWorld"
// 		{"Hello", "World"} with sep = "CS2505" --> "HelloCS2505World"
// Note:
//	Only add sep between two string_t variables, so there shouldn't be
//	an extra sep after "World" in the above examples.
//
// Returns:
//	If a required dynamic allocation fails (i.e. with string_insert()), 
//	the function will return false, true otherwise.
//
bool string_join(string_t * const result,  const string_t * const words, 
			const size_t num_words, const char * const sep);

// Makes a deep copy of *src and stores it in *dest. Similar to *dest = *src.
//
// Pre:
//	src - Points to a valid string_t variable and is not NULL.
//	dest - Points to a valid string_t variable and is not NULL.
//
// Post:
//	If successful then *dest contains a copy of *src. Both *src and *dest
//	should be completely separate entities. Changing one should not 
//	affect the other.
//
// Returns:
//	If copying *src into *dest succeeds the function will return true.
//	If dynamic allocation is required, but fails this function will
//	return false.
//
bool string_copy(string_t * const dest, const string_t * const src);

#endif
