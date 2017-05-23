#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include  "array_ops.h"


int main()
{
	const size_t start_usage = 10;
	int A[ARRAY_MAX_SIZE], B[ARRAY_MAX_SIZE], C[ARRAY_MAX_SIZE];

	srand(time(NULL));

	printf("Create and initialize A, B, and C.\n");
	for (size_t x = 0; x < start_usage; x++)
	{
		// Get a value for A[x].
		A[x] = rand() % 100;

		// Make B[x] a little different than A[x].
		B[x] = A[x] + rand() % 3 + 1; 

		// Make C[x] the same as A[x].
		C[x] = A[x];
	}

	printf("Are A and B are different?\n");
	if (!array_cmp(A, start_usage, B, start_usage))
	{
		printf("A and B are different.\n");
	}

	if(array_cmp(A, start_usage,  C, start_usage))
	{
		printf("A and C are the same.\n");
	}

	int value =  rand() % 100;
	printf("Insert %d at index 0:\n", value);
	size_t ausage = array_insert(A, start_usage, 0, value);

	value =  rand() % 100;
	printf("Insert %d at index %zu:\n", value, ausage / 2);
	ausage = array_insert(A, ausage, ausage / 2, value);

	value = rand() % 100;
	printf("Insert %d at index %zu:\n", value, ausage);
	ausage = array_insert(A, ausage, ausage, value);

	printf("Erase 1 element at index 0\n");
	ausage = array_erase(A, ausage, 0, 1);

	printf("Erase 256 elements at index %zu\n", ausage);
	ausage = array_erase(A, ausage, ausage / 2,  256);

	return 0;

}
