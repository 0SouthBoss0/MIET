#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>
#include <iostream>

#define SIZE1 8
#define SIZE2 8

void initMatrix(int arr[][SIZE2], int size1, int size2) {

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            arr[i][j] = (rand() % 100) * pow(-1.0, rand());
        }
    }
}

void printMatrix(int arr[][SIZE2], int size1, int size2) {
    printf("Array:\n");
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            printf("%d \t", arr[i][j]);
        }
        printf("\n");
    }

}

void solve(int(&a)[SIZE1][SIZE2], int* max, int* min, int size1, int size2) {

    printf("\n Crop array:\n");
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if ((i + j) < size1) {
                printf("%d\t", *(*(a + i) + j));

                *max = (*max < *(*(a + i) + j)) ? *(*(a + i) + j) : *max;
                *min = (*min > *(*(a + i) + j)) ? *(*(a + i) + j) : *min;

                if (*max < *(*(a + i) + j)) {
                    *max = *(*(a + i) + j);
                }
            }
        }
        printf("\n");
    }
}

int main() {

    time_t k;
    srand(time(&k));

    int a[SIZE1][SIZE2];
    initMatrix(a, SIZE1, SIZE2);
    printMatrix(a, SIZE1, SIZE2);

    int ans_max = -100;
    int ans_min = 100;

    int* p_ans_max = &ans_max;
    int* p_ans_min = &ans_min;

    solve(a, p_ans_max, p_ans_min, SIZE1, SIZE2);

    printf("\nMinimum: %d; maximum: %d\n", ans_min, ans_max);

    system("pause");
}