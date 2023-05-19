#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>
#include <iostream>

#define SIZE1 7
#define SIZE2 7

void printDoubleArr(double* arr, int size) {
    printf("\nResult:\n");
    for (int i = 0; i < size; i++) {
        printf("%f \t", *(arr + i));
    }
    printf("\n");
}

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

double getMiddAr(int* stroka, int size2) {
    int csum = 0;
    for (int i = 0; i < size2; i++) {
        csum += stroka[i];
    }
    return static_cast <double> (csum) / size2;
}

void solve(int(&a)[SIZE1][SIZE2], double* answer, int size1, int size2) {

    for (int i = 0; i < SIZE1; i++) {
        double qq = getMiddAr(*(a + i), SIZE2);
        answer[i] = qq;
    }
}

int main() {

    time_t k;
    srand(time(&k));

    double answer[SIZE1];

    int a[SIZE1][SIZE2];
    initMatrix(a, SIZE1, SIZE2);

    solve(a, answer, SIZE1, SIZE2);

    printMatrix(a, SIZE1, SIZE2);
    printDoubleArr(answer, SIZE1);

    system("pause");
}