/* file: factoryy.c */
/* authors: Ravi Maingot (email: r.maingot@student.rug.nl) */
/* date: 26/04/2022 */
/* version: 1.0 */
/* Description: laptop making */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

void *safeCalloc(unsigned long int n, int size) {    
    void *a = calloc(n, size);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeCalloc(%ld) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

unsigned long long int summy(unsigned long int *p, unsigned long int *d, unsigned long int day, unsigned long int size, unsigned long int P) {
    unsigned long long int sum = 0;
    for (unsigned long int i = 0; i < size; i++) {
        sum += (day / d[i]) * p[i];
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

void showArray(unsigned long int length, unsigned long int arr[]) {
    printf("%" SCNu64, arr[0]);
    for (int i=1; i < length; i++) {
        printf(",%" SCNu64, arr[i]);
    }
    printf("\n");
}

int main(int argc, char*argv[]) {
    unsigned long int P, f, pi, di;
    unsigned long int maxd=0, maxp=0;
    
    scanf("%" SCNu64, &P);
    scanf("%" SCNu64, &f);
    unsigned long int *p = (unsigned long int*) safeCalloc(f, sizeof(unsigned long int));
    unsigned long int *d = (unsigned long int*) safeCalloc(f, sizeof(unsigned long int));

    for (int i = 0; i < f; i++) {
        scanf("%" SCNu64 " %" SCNu64, &pi, &di);
        p[i] = pi;
        d[i] = di;
        if (maxd < di) {
            maxd = di;
        }
        if (maxp < pi) {
            maxp = pi;
        }
    }

    unsigned long int x;
    if (P == 0 || maxp == 0) {
        P = P;
    } else {
        x = binarySearch(p, d, maxd/2, 10000000000000000, f, P);
    }
    printf("%" SCNu64 "\n", x);

    free(p);
    free(d);

    return 0;
}