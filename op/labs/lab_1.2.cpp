#include <stdio.h>
#include <stdlib.h>
#include <clocale>

int main() {
	// ����������� �������
	setlocale(LC_ALL, "Russian");

	// ���������� ����������
	char x;
	int a;

	// ����������� ����
	while (1) {
		//���� ������� �������������
		scanf("%c", &x);

		//�������� �� �������� ����� "enter" � ������ ���������
		if (x == 'E' || x == 'e')
			if ((x = getchar()) == 'N' || x == 'n')
				if ((x = getchar()) == 'T' || x == 't')
					if ((x = getchar()) == 'E' || x == 'e')
						if ((x = getchar()) == 'R' || x == 'r')
							break;

		//��������� ���� �������
		a = (int)(x);

		//���� ��������� ������ �� �������� ��������
		if (a != 10) {

			switch (a) {
			case (int)'[':
				printf("���������� ������\n");
				break;

			case (int)']':
				printf("���������� ������\n");
				break;

			case (int)'{':
				printf("�������� ������\n");
				break;

			case (int)'}':
				printf("�������� ������\n");
				break;

			case (int)'(':
				printf("������� ������\n");
				break;

			case (int)')':
				printf("������� ������\n");
				break;

			default:
				printf("�� ������\n");
			}

		}
	}
	system("PAUSE");
	return 1;
}