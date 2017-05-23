#ifndef DUPLICATE_DIGITS_H
#define DUPLICATE_DIGITS_H
#include <stdint.h>

/**
  *  Forms an integer value by duplicating each digit in Value, N times.
  *
  * Examples:
  *     duplicate_digits(12, 1) = 12
  *     duplicate_digits(12, 2) = 1122
  *     duplicate_digits(12, 3) = 111222
  *     duplicate_digits(12, 4) = 11112222
  *     duplicate_digits(12, 5) = 1111122222
  *
  * Pre:      Value and N have been initialized.
  *           N > 0.
  * 
  * Returns:  the integer value formed by duplicating each digit in Value, N 
  *           times. If N = 0, the return value is undefined.
  *
  * Restrictions:
  *    You may use any integer operations supported in C.  You may also
  *    use any selection (if, if..else, etc) or iteration (for, while)
  *    constructs.
  *
  *    You may not use an array or string, nor may you perform 
  *    any I/O operations. Similarly you may not use math.h.
  */ 
uint64_t duplicate_digits(uint64_t Value, uint8_t N);

#endif
