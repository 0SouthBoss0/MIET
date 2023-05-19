#include <stdio.h>
#include <stdlib.h>
#include <clocale>

int main() {
	// русификация текстов
	setlocale(LC_ALL, "Russian");

	// объявление переменных
	char x;
	int a;

	// бесконечный цикл
	while (1) {
		//ввод символа пользователем
		scanf("%c", &x);

		//проверка на введённое слово "enter" в разных регистрах
		if (x == 'E' || x == 'e')
			if ((x = getchar()) == 'N' || x == 'n')
				if ((x = getchar()) == 'T' || x == 't')
					if ((x = getchar()) == 'E' || x == 'e')
						if ((x = getchar()) == 'R' || x == 'r')
							break;

		//получение кода символа
		a = (int)(x);

		//если введенный символ не является пробелом
		if (a != 10) {

			switch (a) {
			case (int)'[':
				printf("Квадратная скобка\n");
				break;

			case (int)']':
				printf("Квадратная скобка\n");
				break;

			case (int)'{':
				printf("Фигурная скобка\n");
				break;

			case (int)'}':
				printf("Фигурная скобка\n");
				break;

			case (int)'(':
				printf("Круглая скобка\n");
				break;

			case (int)')':
				printf("Круглая скобка\n");
				break;

			default:
				printf("Не скобка\n");
			}

		}
	}
	system("PAUSE");
	return 1;
}