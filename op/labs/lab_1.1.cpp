#include <stdio.h>
#include <stdlib.h>
#include <clocale>

int main() {
	// ����������� ������� 
	setlocale(LC_ALL, "Russian");

	// ���������� ����������
	int a, b, c, d;
	double x;

	//����������� ����
	while (1) {

		//���� ���������� �������������
		printf("\n������� a...\n");
		scanf_s("%d", &a);

		printf("\n������� b...\n");
		scanf_s("%d", &b);

		printf("\n������� c...\n");
		scanf_s("%d", &c);

		printf("\n������� d...\n");
		scanf_s("%d", &d);

		//�������� ������ ����� (������� �� ����)
		if (c == 0) {

			//����� ��������� �� ������
			printf("������...\n");
			printf("���������� ���������...\n");

			//����� �������� ��� ���������� ����� ������
			continue;
		}

		//���������� �������� ���������
		x = a + (double)(b) / double(c) + d;

		//����� ����������
		printf("���������: %.2f", x);
		printf("\n");
		printf("��������� ���������...\n");
		break;

	}

	system("PAUSE");
	return 1;
}