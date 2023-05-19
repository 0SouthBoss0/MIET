#include <stdio.h>
#include <stdlib.h>
#include <clocale>

int main() {
	// русификация текстов 
	setlocale(LC_ALL, "Russian");

	// объявление переменных
	int a, b, c, d;
	double x;

	//бесконечный цикл
	while (1) {

		//ввод переменных пользователем
		printf("\nВведите a...\n");
		scanf_s("%d", &a);

		printf("\nВведите b...\n");
		scanf_s("%d", &b);

		printf("\nВведите c...\n");
		scanf_s("%d", &c);

		printf("\nВведите d...\n");
		scanf_s("%d", &d);

		//контроль ошибки ввода (деление на ноль)
		if (c == 0) {

			//вывод сообщения об ошибке
			printf("Ошибка...\n");
			printf("Перезапуск программы...\n");

			//новая итерация для повторного ввода данных
			continue;
		}

		//вычисление значения выражения
		x = a + (double)(b) / double(c) + d;

		//вывод результата
		printf("Результат: %.2f", x);
		printf("\n");
		printf("Программа завершена...\n");
		break;

	}

	system("PAUSE");
	return 1;
}