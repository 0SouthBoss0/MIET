#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  int n, i;
  int s1 = 0;
  int s2 = 0;

  time_t k;
  srand(time(&k));

  printf("Enter n...\n");
  scanf("%d", & n);
    
  //��������� � ����� ��������� ������� ������������ n
  int arr[n];
  printf("Generated array:\n");
  for (i = 0; i < n; i++) {
    arr[i] = (rand() % 100) * pow(-1, rand());
    printf("%d ", arr[i]);

  }
  
  //���������� ������� �������� �������
  int half_array = n / 2 + n % 2;

  //���������� ����� ������������� ��������� ������ �������� �������
  for (i = 0; i < half_array; i++) {
    if (arr[i] > 0) {
      s1 += arr[i];
    }
  }
  
  //���������� ����� ������������� ��������� ������ �������� �������
  for (i = half_array; i < n; i++) {
    if (arr[i] < 0) {
      s2 += arr[i];
    }
  }

  printf("\ns1: %d", s1);
  printf("\ns2: %d", s2);
}