#ifndef FACTORIAL_H
#define FACTORIAL_H
#include <stdint.h>

/* Each call computes and returns the next factorial value starting with 0!.
 * So the first call returns 0!, the next call returns 1!, the next 2!, etc. 
 *
 * Example usage:
 *
 * Factorial() = 1   // first call 
 * Factorial() = 1   // second call
 * Factorial() = 2   // etc...
 * Factorial() = 6
 * Factorial() = 24
 * Factorial() = 120
 *
 *  Restrictions:
 *   - You may not use global variables.
 *   - You may not use any additional libraries.
 *   - You may not make any use of character/string variables or arrays.
 *   - You may not read input or write output.
 *   - You may not use math.h.
 */
uint64_t Factorial();

#endif
