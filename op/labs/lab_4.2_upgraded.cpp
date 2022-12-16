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

int * solve(int ** a, int * max, int * min, int size1, int size2) {

  printf("\n Crop array:\n");
  for (int i = 0; i < size1; i++) {
    for (int j = 0; j < size2; j++) {
      if ((i + j) < size1) {
        printf("%d\t", *( * (a + i) + j));

        * max = ( * max < * ( * (a + i) + j)) ? * ( * (a + i) + j) : * max;
        * min = ( * min > * ( * (a + i) + j)) ? * ( * (a + i) + j) : * min;

      }
    }
    printf("\n");
  }

  static int result[2] = {
    * max,
    * min
  };
  return result;
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
  printf("Matrix:\n");
  printMatrix(Matr, size1, size2);

  int ans_max = -100;
  int ans_min = 100;

  int * p_ans_max = & ans_max;
  int * p_ans_min = & ans_min;

  printf("\nMinimum: %d; maximum: %d\n", *(solve(Matr, p_ans_max, p_ans_min, size1, size2) + 1), * solve(Matr, p_ans_max, p_ans_min, size1, size2));

  free(Matr);
  system("pause");

  return 0;
}