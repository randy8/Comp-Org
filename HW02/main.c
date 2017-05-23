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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100

int main() {
char lineBuffer[MAXLENGTH];
	int x, y, sum;
	double avg;
	int *array = malloc(8*sizeof(int));
	FILE *fp = fopen("ScoreData.txt", "r");
	if (fp == NULL) {
		printf("Error opening file input.txt.\n");
		return 1;
	}
	
	FILE *fr;
	fr = fopen("Results.txt","w");
	while (fgets(lineBuffer, MAXLENGTH, fp) != NULL) {
		sscanf(lineBuffer, "%d-%d %d:%d:%d:%d:%d:%d:%d:%d", &x, &y, 
		&array[0], &array[1], &array[2], &array[3], &array[4], &array[5], &array[6], &array[7]);
			double counter = 0.00;
			sum = 0;
			for (int x = 0; x < 8; x++) {
				sum = sum + array[x];
				if (array[x] != 0){
					counter++;
				}
			}
			
			if (counter != 0) {
				avg = sum/counter;
				long intAvg = (long) avg;
				double decAvg = (avg - intAvg)*100;
				int dec = (int) decAvg;
				fprintf(fr, "%d%5.4d:  %c.%2.2d on %d assignments of ", x, y, intAvg, dec, (int) counter);
				for (int x =0; x<8;x++) {
					if (array[x] != 0) {
						fprintf(fr, "%c", (char) array[x]);
					}
					if ((array[x] == 0) || (x == 7)) {
						fprintf(fr, "\n");
						x = 8;
					}
				}
				for (int x = 0; x < 8; x++) {
					array[x] = 0;
				}
			}
			else {
				fprintf(fr, "%d%d: no score data was read\n", x, y);
			}
		} 
	
	if (!feof(fp)) {
		printf("Failed to read to end of file.\n");
	}

	fclose(fp);
	return 0;
}
