#ifndef BIG_INT_H
#define BIG_INT_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define NUM_BITS 32

/**
 *   Initializes BinInt[] so that the elements correspond to the 2's complement
 *   representation of the 32-bit integer Src.
 * 
 *   Pre:   BinInt[] is of dimension 32
 *   Post:  For i = 0 to 31, BinInt[i] == 2^i bit of Src
 */
void BI_Create(uint8_t BinInt[], int32_t Src);

/**
 *   Converts a BinInt[] to its decimal representation.
 * 
 *   Pre:   Num[] is of dimension 32
 *          Num[] stores a 2's complement representation integer    
 *   Ret:   The decimal value.
 *    
 */
int32_t BI_ToDecimal(const uint8_t Num[]);

/**
 *   Computes sum of 2's complement representations of integer values.
 * 
 *   Pre:   Sum[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement representations
 *   Post:  Sum[] == Left[] + Right[], if possible
 *   Ret:   false if overflow occurs when computing sum of Left[] and Right[];
 *          true otherwise
 */
bool BI_Add(uint8_t Sum[], const uint8_t Left[], const uint8_t Right[]); 

/**
 *   Computes difference of 2's complement representations of integer values.
 * 
 *   Pre:   Diff[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement representations
 *   Post:  Diff[] == Left[] - Right[], if possible
 *   Ret:   false if overflow occurs when computing difference of Left[]
 *          and Right[]; true otherwise 
 */
bool BI_Sub(uint8_t Diff[], const uint8_t Left[], const uint8_t Right[]);

/**
 *   Computes negation of 2's complement representation of integer value.
 * 
 *   Pre:   Neg[] and Right[] are of dimension 32
 *          Right[] stores a 2's complement representation
 *   Post:  Neg[] = -Right[]
 *   Ret:   false if negation cannot be correctly represented; 
 *          true otherwise
 */
bool BI_Neg(uint8_t Neg[], const uint8_t Right[]); 


/**
 *   Prints 2's complement representation, with formatting.
 * 
 *   Pre:   fp is open on an output stream
 *          BinInt[] is of dimension 32 and stores a 2's complement
 *             representation
 *          prefix and suffix are each NULL or point to a C-string
 *   Post:  the bits represented in BinInt[] have been written, preceded by
 *          prefix (if not NULL) and followed by suffix (if not NULL)
 */
void BI_fprintf(FILE* fp, const uint8_t BinInt[], char* prefix, char* suffix);

#endif

