/* file: scalpers.c */
/* author: Ravi Maingot (email: r.maingot@student.rug.nl) */
/* date: 17/04/2022 */
/* version: 5.0 */
/* Description: my code from last year */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

// meijsters safeMalloc but for calloc
void *safeCalloc(long int n) {    
    void *a = calloc(n, sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeCalloc(%ld) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

int main(int argc, char *argv[]) {
	// INPUTING
	int n;
	int start, end;
	int max = 0;
	int* array;
	array = (int*)safeCalloc(1000000); // set the array to a suffienciently large size
									   // to avoid reallocation
	
	scanf("%d\n", &n);
	
	/** 
		This for loop interates through the inputs and increments the appropriate array
		indexes per input.
		The time complexity of the program is therefore O(n * m) where n is the number of inputs
		and m is the number of days between start and end, since most the intervals are quite big, 
		we can assume the time complexity to be O(n^2).
	**/
	for (int i = 0 ; i < n ; i++){
		scanf("%d %d", &start, &end);
		// to find the largest end date of the inputed intervals
		end++; //has to search end too in for loop after
		if (max < end) {
			// intialise indexes for max to end
			for (int j = max ; j < end ; j++) {
				array[j] = 0;
			}
			max = end;
		}
		// a check for if the start day is equal to the end day
		//else increment all the days between start and end
		for (int j = start ; j < end ; j++) {
			array[j]++;
		}
	}

	// OUTPUTING
	int index = 0;
	
	int value = array[0];
	for (int i = 0 ; i < max ; i++) {
		if (array[i] > value){
			value = array[i];
			index = i;
		}
	}
	printf("%d %d\n", index, value);

	free(array);
		
	return 0;
}
