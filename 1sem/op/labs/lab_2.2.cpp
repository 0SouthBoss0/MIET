#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

int main() {

  int arr[SIZE][SIZE];

  time_t k;
  srand(time(&k));
  
  //генерация и вывод элементов матрицы размерностью SIZExSIZE
  printf("Generated array:\n");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      arr[i][j] = (rand() % 100) * pow(-1, rand());
        printf("%d \t", arr[i][j]);
    }
    printf("\n");
  }

  int ans = 0;

  //рассматриваются только элементы матрицы, лежащие в заштрихованной области, данные элементы суммируются
  printf("\nCrop array:\n");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE - i; j++) {
      ans += arr[i][j];
      printf("%d \t", arr[i][j]);
    }
    printf("\n");
  }
  printf("\nSum of crop array: %d\n", ans);

  double ans2[8];

  //вычисление средних арифметических значений строк
  for (int i = 0; i < SIZE; i++) {
    int localsum = 0;
    for (int j = 0; j < SIZE; j++) {
      localsum += arr[i][j];
    }
    ans2[i] = (double)(localsum) / SIZE;
  }

  printf("\nMiddle arithmetic:\n");
  for (int i = 0; i < SIZE; i++) {
    printf("%f\n", ans2[i]);
  }
}