#ifndef BIGMESA_H
#define BIGMESA_H

/**
 *  Given an array of nonnegative integers, a mesa is a sequence of 5 or
 *  more identical values.  The length of a mesa is the number of values
 *  in the sequence, and the mass of a mesa is the sum of the values in
 *  the sequence.
 *
 *  bigMesa() determines the mesa of maximum mass in the array that is
 *  passed into it.  bigMesa() reports its results by setting three extern
 *  variables:  mesaStart, mesaEnd and mesaMass.
 *
 * Pre:  A[0:A_Size - 1] are nonnegative integers.
 * Post: mesaStart = index of first element of most massive mesa
 *       mesaEnd   = index of last element of most massive mesa
 *       mesaMass  = sum of elements in most massive mesa
 *       All are set to zero if no mesa is found.
 *
 * Restrictions:
 *    You may not use a second array.
 */ 
void bigMesa(int A[], int A_Size);

#endif
