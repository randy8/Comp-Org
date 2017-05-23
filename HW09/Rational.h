#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdint.h>
#include <stdbool.h>

struct _Rational {
   int32_t Top;
   int32_t Bottom;
};
typedef struct _Rational Rational;

//-------------------------------------------------------------------- creator
/**
 *  Creates and initializes a new Rational object.
 *  Pre:
 *        Denominator != 0
 *  Returns:
 *        A Rational object X that represents the rational number
 *        Numerator / Demonimator.
 */
Rational Rational_Construct(int32_t Numerator, int32_t Denominator);

//-------------------------------------------------------------------- unary fns
/**
 *   Compute the arithmetic negation of R.
 *   Pre:
 *        R has been properly initialized.
 *   Returns:
 *        A Rational object X such that X + R = 0.
 */
Rational Rational_Negate(const Rational R);

/**
 *   Compute the arithmetic floor of R.
 *   Pre:
 *        R has been properly initialized.
 *   Returns:
 *        The largest integer N such that N <= R.
 */
int32_t Rational_Floor(const Rational R);

//-------------------------------------------------------------------- binary fns
/**
 *   Compute the sum of Left and Right.
 *   Pre:
 *        Left and Right have been properly initialized.
 *   Returns:
 *        A Rational object X equal to Left + Right.
 */
Rational Rational_Add(const Rational Left, const Rational Right);

/**
 *   Compute the product of Left and Right.
 *   Pre:
 *        Left and Right have been properly initialized.
 *   Returns:
 *        A Rational object X equal to Left * Right.
 */
Rational Rational_Multiply(const Rational Left, const Rational Right);


//-------------------------------------------------------------------- relational fns
/**
 *   Determine whether Left and Right are equal.
 *   Pre:
 *        Left and Right have been properly initialized.
 *   Returns:
 *        True if Left == Right, false otherwise.
 */
bool Rational_Equals(const Rational Left, const Rational Right);

/**
 *   Determine whether Left is less than Right.
 *   Pre:
 *        Left and Right have been properly initialized.
 *   Returns:
 *        True if Left < Right, false otherwise.
 */
bool Rational_LessThan(const Rational Left, const Rational Right);

#endif

