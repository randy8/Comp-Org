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

#include "factorial.h"

uint64_t Factorial() {
	static uint64_t count = -1;
	static uint64_t factorial = 1;
	count++;
	
	if (count == 0) {
		return 1;
	}

	factorial *= count;
	return factorial;
}
