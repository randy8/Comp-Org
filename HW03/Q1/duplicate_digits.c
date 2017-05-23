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
#include "duplicate_digits.h"

uint64_t duplicate_digits(uint64_t Value, uint8_t N) {
	uint64_t Accum;

	if (N == 0) {
	   return Accum;
	}
	else if (Value == 0) {
	   return 0;
	}

	Accum = 0;
	uint64_t x = Value, temp = 0, power = 1;
	 
	while (x >= 1) {
		temp = x % 10;
		x /= 10;
		for (uint64_t i = 0; i < N; i++) {
			Accum += temp*power;
			power *= 10;
		  }
	}
	return Accum;
}