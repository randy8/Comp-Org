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

#include "array_ops.h"
#define ARRAY_MAX_SIZE 256
 
bool array_cmp(int lhs[], size_t lusage, int rhs[], size_t rusage) {
    if (lusage == rusage) {
       for (int i = 0; i < lusage; i++) {
               if (lhs[i] == rhs[i]) {
                    return true;
            }
        }
    }
    return false;
}

size_t array_append(int dest[], size_t dusage, int src[], size_t susage) {
    if ((dusage + susage) > ARRAY_MAX_SIZE) {
        return dusage;
    }
    else {
        for (int i = dusage; i < dusage + susage; i++) {
            dest[i] = src[i - susage];
        }
    }

    return dusage + susage;    
}

size_t array_insert(int array[], size_t usage, size_t index, int value) {
    if (index > usage || usage > ARRAY_MAX_SIZE) {
        return usage;
    }
    else {
        for (int i = usage; i > index; i--) {
            array[i] = array[i-1];
        }
        array[index] = value;
    }   
    return usage + 1;
}



size_t array_erase(int array[], size_t usage, size_t index, size_t count) {
    if (index >= usage) {
        return usage;
    }
    if ((index + count) >= usage) {
        return index;
    }
    else {
        for (int i = index + count; i < usage; i++) {
            array[i] = array[i+count];
        }
        return usage - count;
    }
}