/* file: factoryy.c */
/* authors: Ravi Maingot (email: r.maingot@student.rug.nl) 
            Aidan Adelaar (email: a.adelaar@student.rug.nl*/
/* date: 26/04/2022 */
/* version: 9.0 */
/* Description: laptop making */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

// meajsters safeMalloc but for calloc
void *safeCalloc(unsigned long int n, int size) {    
    void *a = calloc(n, size);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeCalloc(%ld) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

/** 
 * this function gets given a day and then using that day a number of products is then
 * determined using math by iterating thru the entire input array (p & d simultaeously)
 * to return a boolean value indicating whether or not the day is a "valid day" meaning
 * greater or equal to P. This function has a time complexity of O(n).
**/
unsigned long long int summy(unsigned long int *p, unsigned long int *d, unsigned long int day, unsigned long int size, unsigned long int P) {
    unsigned long long int sum = 0;
    for (unsigned long int i = 0; i < size; i++) {
        sum += (day / d[i]) * p[i]; // the math
        if (sum >= P) {
            break;
        }
    }
    if (sum >= P){
        return 1;
    } else {
        return 0;
    }
    return sum;
}

/** implemented the binary search from the slides; this should yeild a time complexity of O(log(n))
 * but since we running the summy function upon every iteration the time complexity is therefore
 * => O(n * log(n))
**/
unsigned long int binarySearch(unsigned long int *p, unsigned long int *d, unsigned long int low, unsigned long int high, unsigned long int size, unsigned long int P) {
    if (low > high) {
        return -1;
    }
    unsigned long int mid = low + (high - low) / 2;
    if (summy(p, d, mid, size, P) == 1 && summy(p, d, mid-1, size, P) == 0) {
        return mid;
    } else if (summy(p, d, mid, size, P)==0) {
        return binarySearch(p, d, mid + 1, high, size, P);
    } else {
        return binarySearch(p, d, low, mid - 1, size, P);
    }
}

int main(int argc, char*argv[]) {
    //DECLARING & INPUTING VARIABLES
    unsigned long int P=0, f, pi, di;
    unsigned long int maxd=0, maxp=0;
    
    scanf("%" SCNu64, &P);
    scanf("%" SCNu64, &f);
    unsigned long int *p = (unsigned long int*) safeCalloc(f, sizeof(unsigned long int));
    unsigned long int *d = (unsigned long int*) safeCalloc(f, sizeof(unsigned long int));

    for (int i = 0; i < f; i++) {
        scanf("%" SCNu64 " %" SCNu64, &pi, &di);
        p[i] = pi;
        d[i] = di;
        // taking the maximum input day to then create an acceptable 'lower bound'
        // for the binary search
        if (maxd < di) {
            maxd = di;
        }
        // i wrote this in the try get TC 2 working, still couldnt do it
        // ideally this wouldve been the disregard a list of factories that
        // make a sum total of 0 laptops
        if (maxp < pi) {
            maxp = pi;
        }
    }

    //BINARY SEARCH
    unsigned long int x=0;
    if (P != 0 && maxp != 0) {
        // a suffieciently large 'upper bound' to ensure the binary search succeeds
        x = binarySearch(p, d, maxd/2, 10000000000000000, f, P);
    }

    //OUTPUT
    printf("%" SCNu64 "\n", x);

    //FREEING MEMORY
    free(p);
    free(d);

    return 0;
}