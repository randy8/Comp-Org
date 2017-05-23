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
#include <stdlib.h>     
#include <stdbool.h>    
#include <stdint.h>     
#include <inttypes.h>   
#include <string.h>
#include <time.h>
#include "Untangle.h"

/**
* Untangle() parses a chain of records stored in the memory region pointed
* to by Buffer and writes a report to the supplied file stream. Formatting
* details are provided in the specification for the assignment.
*
* Pre: Buffer points to a region of memory formatted as specified.
* Log points to an opened text file.
*
* Post: The target of Buffer has been parsed and a report written as
* specified.
*
* Returns: the number of tokens in the supplied quotation.
*
*/
uint8_t Untangle(uint8_t* Buffer, FILE* Log) {
    uint8_t count = 0;
    uint8_t buff = *Buffer;
    uint16_t offset = *((uint16_t*) (Buffer + 1));
    fprintf(Log, "Looking for %u words, starting at %X", buff, offset); // u is unsigned, X is hex
	fprintf(Log, "\n");

	while (count < buff) {
        fprintf(Log, "%X: ", offset);	
		uint8_t length = *(Buffer + offset);

        for(int i = 1; i < length + 1; i++) {
            fprintf(Log, "%c", *(Buffer + offset + i)); // ASCII key
        }
        fprintf(Log, "\n");
        count++; 
        offset = *((uint16_t*) (Buffer + 1 + (2*count)));
    }
    return count;
}
