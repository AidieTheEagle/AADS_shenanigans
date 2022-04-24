/* file: factory.c */
/* authors: Ravi Maingot (email: r.maingot@student.rug.nl) */
/* date: 16/04/2022 */
/* version: 1.0 */
/* Description: laptop making */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

void *safeCalloc(long int n, int size) {    
    void *a = calloc(n, size);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeCalloc(%ld) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}


int main(int argc, char*argv[]) {
    int P;
    int f;
    int pi, di, maxd=0, mind=1000000;

    scanf("%d", &P);
    scanf("%d", &f);

    int **arr = (int**) safeCalloc(f, sizeof(int*));
    for (int i = 0; i < f; i++) {
        arr[i] = (int*) safeCalloc(2, sizeof(int));
    }
    
    for (int i = 0; i < f; i++) {
        scanf("%d %d", &pi, &di);
        arr[i][0] = pi;
        arr[i][1] = di;
        if (maxd < di) {
            maxd = di;
        }
        if (mind > di) {
            mind= di;
        }
    }

    // for (int i = 0; i < f; i++) {
    //     printf("%d %d\n", arr[i][0], arr[i][1]);
    // }
    int laptopSum = 0;
    int i = mind-1;
    if (P == 0) {
        printf("0\n");
    } else {
        while(1) {
            //printf("day:%d. %d\n", i, laptopSum);
            if (laptopSum >= P || i == maxd) {
                break;
            }
            i++;
            for (int j = 0; j < f; j++) {
                if (arr[j][1] <= i && i % arr[j][1] == 0) {
                    // printf("%d <= %d && %d \n", arr[j][1], i, i % arr[j][1]);
                    // printf("+%d\n", arr[j][0]);
                    laptopSum += arr[j][0];
                }
                
                if(laptopSum >= P) {
                    break;
                }
            }
        }
        printf("%d %d\n", P, i);
    }

    for (int i = 0; i < f; i++) {
        free(arr[i]);
    }
    free(arr);
    
    return 0;
}