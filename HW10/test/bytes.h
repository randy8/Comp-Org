#ifndef BYTES_H
#define BYTES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#define DEFAULT_SIZE 16
#define BYTES_PER_LINE 16

// Enumeration for the different data sizes.  
enum width_t {BITS8, BITS16, BITS32, BITS64};
typedef enum width_t width_t;

// Enumeration for byte order. 
enum endian_t {BIG, LITTLE}; 
typedef enum endian_t endian_t;

// Range type, used to iterate through the bytes type.
struct range_t
{
	size_t start;
	size_t stop;
	int64_t step;
};

typedef struct range_t range_t;

// Bytes type, represents an array of byte-sized values. 
struct bytes_t 
{
	// Automatically allocated default buffer. This is used to store the
	// bytes until usage > DEFAULT_SIZE, then we switch to using dynamic 
	// memory (data). dflt is never used again once the switch occurs.
	uint8_t dflt[DEFAULT_SIZE];

	// Initially NULL, points to the dynamically allocated array of bytes.
	uint8_t *data;
	
	// The number of slots or bytes in use, initially 0.
	size_t usage;
	// Actual size of the array, initially DEFAULT_SIZE. 
	size_t dim;
};

typedef struct bytes_t bytes_t;

// Instructor provided functions:

// Initializes a bytes_t variable.
// 
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
// 
// Post:
//	data - Is initialized to NULL.
//	usage - Is initialized to 0.
//	dim - Is initialized to DEFAULT_SIZE.
//
void bytes_init(bytes_t * const bytes);

// Deallocates any dynamic memory allocated for *bytes.
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Post:
// 	Frees any dynamically allocated for the *bytes variable.
//	Sets bytes->data = NULL.
//
void bytes_free(bytes_t * const bytes);

// Prints the *bytes variable in a human readable form, kind of like hexdump.
//
// Pre:
//	out - Points to an open file stream.
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Post:
//	A formatted table is printed.
//
void bytes_fprintf(FILE * out, const bytes_t * const bytes);

// Status functions, these are one-liners:

// Is *bytes empty?
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Returns:
// 	Returns true if bytes->usage is 0, false otherwise.
//
bool bytes_empty(const bytes_t * const bytes);

// Accessor function, gets the raw uint8_t pointer, either bytes->dflt 
// or bytes->data.
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Returns:
// 	If bytes->data is NULL, bytes->dflt is returned, otherwise
// 	bytes->data is returned.
//
uint8_t * bytes_data(const bytes_t * const bytes);


// Accessor function, gets the usage of the bytes_t, bytes->usage.
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Returns:
// 	Returns bytes->usage.
//
size_t bytes_usage(const bytes_t * const bytes); 

// More complex functions that provide common operations for the bytes_t type:

// Sets one byte in the bytes_t variable.
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Post:
//	If index < usage, then the byte at that index has been set to val.
//
// Returns:
//	If the byte at index was set (i.e. index < usage) the function will 
//	return true, false otherwise.
//
bool bytes_set(bytes_t * const bytes, size_t index, uint8_t val);

// Gets a 1 byte, 2 byte, 4 byte, or 8 byte value from *bytes, and
// interprets it as either a big or little endian value.
//
// Enumerations are provided for both the width (width_t) and byte
// order (endian_t). These enumerations can be used as more than just
// a constant to compare against. Since they are integer values they 
// might be used as part of the computation.
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Post:
//	Tries to read a width sized value and interprets it as if it had
//	order, byte ordering. The result is stored in output variable, result. 
//
// Returns:
//	If there are enough bytes starting at index to get a width sized
//	value the function returns true, false otherwise.
//
// Examples:
//	If bytes->data (or dlft) contains the bytes: {0xDE, 0xAD, 0xBE, 0xEF} 
//
//	If we interpret it as a 4 byte value, then in big endian order it
//	is 0xDEADBEEF, the highest order byte is in the lowest index, 0.
//
//	In little endian order it would be interpreted as 0xEFBEADDE, 
//	the highest order byte is in the largest index, 3.
//
//
bool bytes_get(const bytes_t * const bytes, size_t index, 
		width_t width, endian_t order, uint64_t * const result);

// Inserts len bytes, stored in the memory pointed to by buf, into *bytes
// starting at the specified index.
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//	buf - Points to a chunk of memory len bytes long.
//
// Post:
//	The bytes pointed to by buf are inserted into *bytes starting at index. 
//
//	If bytes->usage + len exceeds DEFAULT_SIZE when using bytes->dflt, 
//	the function will switch to dynamically allocated memory, using malloc
//	and copying the current bytes into bytes->data. 
//
//	When already using bytes->data, the memory may be resized when
//	bytes->usage + len > bytes->dim. 
//
// Returns:
//	If a required dynamic allocation fails, or index > bytes->usage
//	the function will return false, true otherwise.
//
// Other thoughts:
// 	You are going to insert "before" index. So if you insert at index = 0 
//	you are inserting before the first byte. Further, if you were to insert 
//	at index = bytes->usage, it's like appending the bytes at the end.
//
//	Reallocate (or just allocate) when bytes->usage + len > bytes->dim.
//	To avoiding reallocating every time you insert, double the needed
//	size, i.e. bytes->dim = 2 * (bytes->usage + len)
//
//
bool bytes_insert(bytes_t * const bytes, size_t index, 
			const uint8_t * buf, size_t len);

// Erases up to len bytes from *bytes starting at the specified index.
//
// Pre:
//	bytes - Points to a valid bytes_t variable and is not NULL.
//
// Post:
//	If index < bytes->usage, then up to len bytes have been erased from
//	*bytes starting at index. When index + len > bytes->usage less than
//	len bytes will be erased.
//
// Returns:
//	If index >= bytes->usage, then no erasure occurs and the function
//	returns false, true otherwise.
//
bool bytes_erase(bytes_t * const bytes, size_t index, size_t len);


// A different way to iterate through a bytes_t type.
//
// This function makes use of the range_t type, which allows us to specify
// range of bytes that we want to examine or modify. The range is inclusive
// at the start, and exclusive at the end. So if a range starts 0 and stops
// at 10, we would examine bytes from 0, up to but not including 10.
//
// For example:
// 	This will iterate through every byte when used with bytes_range():
// 		range_t r1 = {.start = 0, .end = bytes->usage, .step = 1};
//
// 	This will iterate through every other byte when used with 
//	bytes_range():
// 		range_t r2 = {0, bytes->usage, 2};
//
// 	This starts at index 10 and goes down to but not including index 4, 
//	4 bytes at a time:
// 		range_t r3 = {10, 4,  -4};
//
// 	You will modify the range object once every time the function runs. 
//	It's up to you to make sure you don't go out of bounds, but this 
//	should be evaluated lazily. 
//	
//	One call to the function updates the range object just once, so 
//	successive calls are required to iterate through the whole range.
// 
// Returns:
//	A pointer to the next element in bytes->data (or bytes->dflt), 
//	or NULL if there isn't a next element.
//
uint8_t * bytes_range(const bytes_t * const bytes, range_t * const range);


// Makes a deep copy of *src and stores it in *dest. Similar to *dest = *src.
//
// Pre:
//	src - Points to a valid bytes_t variable and is not NULL.
//	dest - Points to a valid bytes_t variable and is not NULL.
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
bool bytes_copy(bytes_t * const dest, const bytes_t * const src);


#endif
