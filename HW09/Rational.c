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
// was obtained from another source, such as a textbook or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Curator System.
//
// Randy Liang

#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdint.h>
#include <stdbool.h>

struct _Rational {
   int32_t Top;
   int32_t Bottom;
};

typedef struct _Rational Rational; //alias
//-------------------------------------------------------------------- creator
/**
 *  Creates and initializes a new Rational object.
 *  Pre:
 *        Denominator != 0
 *  Returns:
 *        A Rational object X that represents the rational number
 *        Numerator / Demonimator.
 */
Rational Rational_Construct(int32_t Numerator, int32_t Denominator)
{
    Rational newR;
    if (Numerator < 0 && Denominator < 0 || Numerator >= 0 && Denominator < 0) {
        Numerator = -Numerator; 
        Denominator = -Denominator; 
    } 
    newR.Top = Numerator; 
    if (Denominator == 0) {
        newR.Bottom = 0;
    } 
    else {
        newR.Bottom = Denominator;
    }
    return newR;
}
//-------------------------------------------------------------------- unary fns
/**
 *   Compute the arithmetic negation of R.
 *   Pre:
 *        R has been properly initialized.
 *   Returns:
 *        A Rational object X such that X + R = 0.
 */
Rational Rational_Negate(const Rational R) {
    Rational negR;
    negR.Top = -R.Top;
    negR.Bottom = R.Bottom;
    return negR;
}

/**
 *   Compute the arithmetic floor of R.
 *   Pre:
 *        R has been properly initialized.
 *   Returns:
 *        The largest integer N such that N <= R.
 */
int Rational_Floor(const Rational R) {
    if (R.Top > 0) {
        return R.Top / R.Bottom;
    } 
    else {
        if (R.Top % R.Bottom == 0) { // integer quotient doesn't need rounding
          return R.Top / R.Bottom;
        } 
        else {
          return (R.Top / R.Bottom) - 1; // floor function rounds down
        }
    }
}
//-------------------------------------------------------------------- binary fns
/**
 *   Compute the sum of Left and Right.
 *   Pre:
 *        Left and Right have been properly initialized.
 *   Returns:
 *        A Rational object X equal to Left + Right.
 */
Rational Rational_Add(const Rational Left, const Rational Right) {
    Rational sum;
    sum.Top = (Left.Top * Right.Bottom) + (Right.Top * Left.Bottom);
    sum.Bottom = Left.Bottom * Right.Bottom;
    return sum; 
}

/**
 *   Compute the product of Left and Right.
 *   Pre:
 *        Left and Right have been properly initialized.
 *   Returns:
 *        A Rational object X equal to Left * Right.
 */
Rational Rational_Multiply(const Rational Left, const Rational Right) {
    Rational product;
    product.Top = Left.Top * Right.Top;
    product.Bottom = Left.Bottom * Right.Bottom;
    return product;
}
//-------------------------------------------------------------------- relational fns
/**
 *   Determine whether Left and Right are equal.
 *   Pre:
 *        Left and Right have been properly initialized.
 *   Returns:
 *        True if Left == Right, false otherwise.
 */
bool Rational_Equals(const Rational Left, const Rational Right) {
    return Left.Top * Right.Bottom == Left.Bottom * Right.Top; //cross multiply: a/b = c/d (i.e. ad = bc)
}

/**
 *   Determine whether Left is less than Right.
 *   Pre:
 *        Left and Right have been properly initialized.
 *   Returns:
 *        True if Left < Right, false otherwise.
 */
bool Rational_LessThan(const Rational Left, const Rational Right) {
    return Left.Top * Right.Bottom < Left.Bottom * Right.Top; 
}
#endif