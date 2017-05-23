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
#include "BinaryInt.h"
#include <inttypes.h>
#define NUM_BITS 32

// Internal representation stores bits so that coefficient of 2^i is at index i.

/**
 *   Initializes BinInt[] so that the elements correspond to the 2's complement
 *   representation of the 32-bit integer Src.
 * 
 *   Pre:   BinInt[] is of dimension 32
 *   Post:  For i = 0 to 31, BinInt[i] == 2^i bit of Src
 */
void BI_Create(uint8_t BinInt[], int32_t Src) 
{
    int32_t Mask = 0x01;
    for (int pos = 0; pos < NUM_BITS; pos++) {
		BinInt[pos] = (Src & Mask) ? 1 : 0;
		Mask = Mask << 1;
   }
}

/**
 *   Converts a BinInt[] to its decimal representation.
 * 
 *   Pre:   Num[] is of dimension 32
 *          Num[] stores a 2's complement representation integer 
 *   Ret:   The decimal value.
 *    
 */
int32_t BI_ToDecimal(const uint8_t Num[])
{
	int32_t dec = 0;
	for (int i = 0; i < 32; i++ ) {
		int32_t n = 1;

		if (Num[i] == 1) {
			for (int j = 0; j < i; j++) {
				n *= 2;
			}
			dec += n; 
		}
	}
	return dec;
}

/**
 *   Computes sum of 2's complement representations of integer values.
 * 
 *   Pre:   Sum[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement representations
 *   Post:  Sum[] == Left[] + Right[], if possible
 *   Ret:   false if overflow occurs when computing sum of Left[] and Right[];
 *          true otherwise
 */
bool BI_Add(uint8_t Sum[], const uint8_t Left[], const uint8_t Right[]) 
{
	int32_t carry = 0; //if both 0, 0
	int32_t carry1 = 0;

	for(int i = 0; i < 32; i++) {  
		carry1 = carry;

		if (Left[i] + Right[i] + carry == 0) {
			Sum[i] = 0;
			carry = 0;
		}
		else if (Left[i] + Right[i] + carry == 1) {
			Sum[i] = 1;
			carry = 0;
		}
		else if (Left[i] + Right[i] + carry == 2) {
			Sum[i] = 0;
			carry = 1;
		}
		else {
			Sum[i] = 1;
			carry = 1;
		}
	}
	
	if (carry == carry1) {
		return true;
	}
	else {
		return false;
	}
}

/**
 *   Computes difference of 2's complement representations of integer values.
 * 
 *   Pre:   Diff[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement representations
 *   Post:  Diff[] == Left[] - Right[], if possible
 *   Ret:   false if overflow occurs when computing difference of Left[]
 *          and Right[]; true otherwise 
 */
bool BI_Sub(uint8_t Diff[], const uint8_t Left[], const uint8_t Right[]) 
{
	int32_t carry = 0; //if both 0, 0
	int32_t carry1 = 0;

	for (int i = 0; i < 32; i++) {  
		carry1 = carry;
		if (Left[i] - Right[i] - carry == 0) {
			Diff[i] = 0;
			carry = 0;
		}
		else if (Left[i] - Right[i] - carry == 1) {
			Diff[i] = 1;
			carry = 0;
		}
		else if (Left[i] - Right[i] - carry == -1) {
			Diff[i] = 1;
			carry = 1;
		}
		else {
			Diff[i] = 0;
			carry = 1;
		}
	}
	if (carry == carry1) {
		return true;
	}
	else {
		return false;
	} 
}

/**
 *   Computes negation of 2's complement representation of integer value.
 * 
 *   Pre:   Neg[] and Right[] are of dimension 32
 *          Right[] stores a 2's complement representation
 *   Post:  Neg[] = -Right[]
 *   Ret:   false if negation cannot be correctly represented; 
 *          true otherwise
 */
bool BI_Neg(uint8_t Neg[], const uint8_t Right[]) 
{
	if (BI_ToDecimal(Right) == -2147483648) {
		return false;
	}
		
    for (int i = 0; i < 32; i++) {
	    if (Right[i] == 0) {
	   		Neg[i] = 1;
	   	}
		else {
	    	Neg[i] = 0;
		}
    }
   
    bool found = true;
    int32_t count = 0;
   
    while (found) {
		if (Neg[count] == 0) {
			Neg[count] = 1;
			found = false;
		}
		else {
			Neg[count] = 0;
			count++;
		}
    }
   	return true;
}

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
void BI_fprintf(FILE* fp, const uint8_t BinInt[], char* prefix, char* suffix) 
{
    if ( prefix != NULL) {
		fprintf(fp, prefix);
    }
	  
    for (int pos = NUM_BITS - 1; pos >= 0; pos--) {
	    if (pos < NUM_BITS - 1 && pos % 4 == 3) {
			fprintf(fp, " ");
	    }
	 
		fprintf(fp, "%"PRIu8, BinInt[pos]);
   }
   
    if ( suffix != NULL) {
		fprintf(fp, suffix);
    }
}
