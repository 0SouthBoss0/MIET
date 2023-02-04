#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>
#include <iostream>
#include <windows.h>

//вывод массива
void printArr(int* arr, int size) {
    printf("\nResult:\n");
    for (int i = 0; i < size; i++) {
        printf("%d \t", *(arr + i));
    }
    printf("\n");
}

//вывод матрицы
void printMatrix(int** matrix, int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            printf("%d \t", matrix[i][j]);
        }
        printf("\n");
    }
}

//подсчет сумм столбцов выделенной области
int* solve(int** a, int* ansArr, int size1, int size2, HANDLE h) {

    printf("\n Crop matrix:\n");

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (((i < size1 / 2 + size1 % 2) && (j < size2 / 2 + size2 % 2)) || (((size1 / 2 <= i) && (i < size1)) && ((size2 / 2 <= j) && (j < size2)))) {
                SetConsoleTextAttribute(h, 2);
                printf("%d \t", a[i][j]);
                SetConsoleTextAttribute(h, 15);
                ansArr[j] += a[i][j];
            }
            else {
                printf("%d \t", a[i][j]);
            }
        }
        printf("\n");
    }

    if (size1 % 2 == 1 && size2 % 2 == 1) {
        ansArr[size2 / 2] -= a[size1 / 2][size2 / 2];
    }
    return ansArr;
}

int main() {

    time_t k;
    srand(time(&k));

    //получаем окно в консоли, в котором будем изменять цвет
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);

    int size1;
    int size2;

    scanf("%d", &size1);
    scanf("%d", &size2);

    //инициализация матрицы
    int** Matr = new int* [size1];
    for (int i = 0; i < size1; ++i)
        Matr[i] = new int[size2];

    //заполнение матрицы
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            Matr[i][j] = (rand() % 100) * pow(-1.0, rand());
        }
    }

    printf("Matrix:\n");
    printMatrix(Matr, size1, size2);

    int* ansArr = new int[size2];
    for (int i = 0; i < size2; i++) {
        ansArr[i] = 0;
    }

    solve(Matr, ansArr, size1, size2, h);

    printArr(ansArr, size2);
    free(Matr);
    free(ansArr);
    system("pause");

    return 0;
}