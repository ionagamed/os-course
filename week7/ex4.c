#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

size_t _min_custom(size_t a, size_t b) {
    return a < b ? a : b;
}

void * _realloc_custom(void *ptr, size_t old_size, size_t new_size) {
    if (!ptr && !new_size) return NULL;

    void *new_ptr;
    if (new_size) {
        new_ptr = malloc(new_size);
        if (ptr) {
            memcpy(new_ptr, ptr, _min_custom(new_size, old_size));
        }
    }
    if (ptr) {
        free(ptr);
    }

    return new_ptr;
}

int main() {
    /**
     * Code below borrowed from the previous excercise, except for the realloc() call change to _realloc_custom()
     */



    // Allows you to generate random number
	srand(time(NULL));

	// Allows user to specify the original array size, stored in variable n1.
	printf("Enter original array size: ");
	int n1 = 0;
	scanf("%d", &n1);

	// Create a new array of n1 ints
	int *a1 = calloc(n1, sizeof(int));
	int i;
	for(i = 0; i < n1; i++) {
		// Set each value in a1 to 100
		a1[i] = 100;
		
		// Print each element out (to make sure things look right)
		printf("%d ", a1[i]);
	}

	// User specifies the new array size, stored in variable n2.
	printf("\nEnter new array size: ");
	int n2 = 0;
	scanf("%d", &n2);

	// Dynamically change the array to size n2
	a1 = _realloc_custom(a1, n1 * sizeof(int), n2 * sizeof(int));

	// If the new array is a larger size, set all new members to 0. Reason: dont want to use uninitialized variables.
	if (n2 > n1) {
        for (i = n1; i < n2; i++) {
            a1[i] = 0;
        }
    }
	
	for(i = 0; i < n2; i++){
		// Print each element out (to make sure things look right)
		printf("%d ", a1[i]);
	}
	printf("\n");
	
	//Done with array now, done with program :D
	
	return 0;
}