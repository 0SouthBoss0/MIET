#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>
#include <iostream>

void printMatrix(int ** matrix, int size1, int size2) {
  for (int i = 0; i < size1; i++) {
    for (int j = 0; j < size2; j++) {
      printf("%d \t", matrix[i][j]);
    }
    printf("\n");
  }
}

double getMiddAr(int * stroka, int size2) {
  int csum = 0;
  for (int i = 0; i < size2; i++) {
    csum += stroka[i];
  }
  return static_cast < double > (csum) / size2;
}

void solve(int ** matrix, double * answer, int size1, int size2) {

  for (int i = 0; i < size1; i++) {
    double qq = getMiddAr( * (matrix + i), size2);
    answer[i] = qq;
  }
}

void printDoubleArr(double * arr, int size) {
  printf("\nResult:\n");
  for (int i = 0; i < size; i++) {
    printf("%f \t", *(arr + i));
  }
  printf("\n");
}

int main() {
  time_t k;
  srand(time( & k));

  int size1;
  int size2;

  scanf("%d", & size1);
  scanf("%d", & size2);
  int ** Matr; // указатель на динамическую матрицу

  int i, j;

  // выделение памяти под массив указателей на строки матрицы
  Matr = (int ** ) malloc(sizeof( * Matr) * size1);

  // выделение памяти под строки матрицы
  for (i = 0; i < size1; i++) {
    Matr[i] = (int * ) malloc(sizeof( * Matr[i]));

    // Инициализация
    for (j = 0; j < size2; j++) {
      Matr[i][j] = (rand() % 100) * pow(-1.0, rand());
    }
  }
  printMatrix(Matr, size1, size2);

  double * answer;
  answer = (double * ) malloc(sizeof( * answer) * size1);

  solve(Matr, answer, size1, size2);
  printDoubleArr(answer, size1);

  free(Matr);
  free(answer);
  system("pause");

  return 0;
}