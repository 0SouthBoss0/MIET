#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>

#define SIZE1 8
#define SIZE2 8

//поиск индекса последнего положительного элемента массива
int findIndex(int arr[], int size) {
  for (int i = size - 1; i >= 0; i--) {
    if (arr[i] > 0) {
      return i;
    }
  }
  return -1;
}

//поиск минимального элемента в массиве до индекса
int solve(int arr[], int size, int index) {
  if (index == -1) {
    printf("\nGenerated array has no positive numbers:\n");
    return 0;
  }
  int len1 = index + 1;
  int min_element = 999999999;

  for (int i = 0; i < len1; i++) {
    if (arr[i] < min_element) {
      min_element = arr[i];
    }
  }
  return min_element;
}

int main() {

  // русификаци€ текстов 
  setlocale(LC_ALL, "Russian");

  //инициализаци€ массивов
  int a[SIZE1];
  int b[SIZE2];

  time_t k;
  srand(time( & k));

  //генераци€ массивов
  for (int i = 0; i < SIZE1; i++) {
    a[i] = (rand() % 100) * pow(-1.0, rand());
  }
  for (int i = 0; i < SIZE2; i++) {
    b[i] = (rand() % 100) * pow(-1.0, rand());
  }

  //вывод исходных массивов
  printf("Array A:\n");
  for (int i = 0; i < SIZE1; i++) {
    printf("%d \t", a[i]);
  }
  printf("\n");

  printf("Array B:\n");
  for (int i = 0; i < SIZE2; i++) {
    printf("%d \t", b[i]);
  }
  printf("\n");

  //индексы последних положительных элементов массивов
  int last_positive_index_1 = findIndex(a, SIZE1);
  int last_positive_index_2 = findIndex(b, SIZE2);

  printf("\nћинимальный элемент в первой части массива A: %d \n", solve(a, SIZE1, last_positive_index_1));
  printf("ћинимальный элемент в первой части массива B: %d \n", solve(b, SIZE2, last_positive_index_2));

  system("pause");
}