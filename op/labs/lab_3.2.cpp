#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale>

#define SIZE1 10
#define SIZE2 8

//�������� ������������� ��������� � �������� ������� �������������� �������
int minimumOfPositiveNumber(int arr_local[][SIZE2], int size1, int size2, int stolbetc) {

  
  int middle_index = size1 / 2 + size1 % 2;
  int min_element = 100;

  for (int i = middle_index; i < size1; i++) {

    if (arr_local[i][stolbetc] > 0 && arr_local[i][stolbetc] < min_element) {
      min_element = arr_local[i][stolbetc];
    }
  }
  return min_element;
}

int main() {
  // ����������� ������� 
  setlocale(LC_ALL, "Russian");

  int arr[SIZE1][SIZE2];

  time_t k;
  srand(time( & k));

  //��������� � ����� ��������� ������� ������������ SIZE1xSIZE2
  printf("Generated array:\n");
  for (int i = 0; i < SIZE1; i++) {
    for (int j = 0; j < SIZE2; j++) {
      arr[i][j] = (rand() % 100) * pow(-1.0, rand());
      printf("%d \t", arr[i][j]);
    }
    printf("\n");
  }
  
  printf("\nCrop array:\n");
  for (int i = SIZE1 / 2 + SIZE1 % 2; i < SIZE1; i++) {
    for (int j = 0; j < SIZE2; j++) {
      printf("%d \t", arr[i][j]);
    }
    printf("\n");
  }

   printf("\n�������� ������������� ���������:\n");
  
  for (int i = 0; i < SIZE2; i++) {
    int qq = minimumOfPositiveNumber(arr, SIZE1, SIZE2, i);
    if (qq == 100) {
      printf("� ������ ����� ������� ��� ������������� ���������:\n");
    } else {
      printf("%d \t", qq);
    }
  }
  printf("\n");
  system("pause");
}