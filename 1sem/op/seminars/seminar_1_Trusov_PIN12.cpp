#include <stdio.h>
#include <clocale>
#include <stdlib.h>
#include <iostream>

int main() {

	// русификация текстов 
	setlocale(LC_ALL, "Russian");

	// переменные, отвечающие за состояние и выход из циклов
	int status = 1;
	int current_status = 0;

	printf("Задачи на самостоятельное выполнение. Вариант 1.\n");

	// основной цикл работы программы
	while (status) {
		printf("Введите номер задачи(1-3). Для завершения работы введите 0: ");

		int task_chosen;
		scanf_s("%d", &task_chosen);

		// переход к задаче, выбранной пользователем
		switch (task_chosen) {

			// завершение работы
		case 0:
			status = 0;
			printf("\nПрограмма завершена.\n");
			break;

			// задача 1
		case 1:
			current_status = 1;
			while (current_status) {
				printf("\nЗадача 1. Вычислить значение (x = a * b / с); a, b, с ввести с клавиатуры.\n");

				int a, b, c;
				double x;

				printf("Введите a: ");
				scanf_s("%d", &a);
				printf("Введите b: ");
				scanf_s("%d", &b);
				printf("Введите c: ");
				scanf_s("%d", &c);


				if (c == 0) {
					printf("Ошибка. C не может быть равно нулю. Задача перезапущена.\n");
					continue;
				}
				else {
					x = (double)(a * b) / (double)(c);
					printf("\nВаш ответ на задачу: ");
					printf("%f\n", x);
					current_status = 0;
				}
			}
			break;

			// задача 2
		case 2:
			current_status = 1;
			while (current_status) {
				printf("\nЗадача 2. Для целого числа k (вводить с клавиатуры) от 1 до 130 вывести фразу «Мне k лет».\n");
				int k;
				scanf_s("%d", &k);

				if (k > 130 || k < 0) {
					printf("Ошибка. k не в диапазоне от 1 до 130. Задача перезапущена.\n");
					continue;
				}

				if (k % 10 == 0 || k % 10 >= 5 || k == 0 || (11 <= k && k <= 14)) {
					printf("\nМне %d лет.\n", k);
				}
				else {
					if (k % 10 == 1) {
						printf("\nМне %d год.\n", k);
					}
					else {
						printf("\nМне %d года.\n", k);

					}
				}
				current_status = 0;
			}
			break;

			// задача 3
		case 3:
			current_status = 1;
			while (current_status) {
				printf("\nЗадача 3. Поле шахматной доски определено парой натуральных чисел (значения от 0 до 8). Ввести координаты 2-х полей k,l и m,n. Определить являются ли они полями одного цвета.\n");
				int k, l, m, n;

				printf("Введите k: ");
				scanf_s("%d", &k);
				printf("Введите l: ");
				scanf_s("%d", &l);
				printf("Введите m: ");
				scanf_s("%d", &m);
				printf("Введите n: ");
				scanf_s("%d", &n);

				if ((k + l) % 2 == (m + n) % 2) {
					printf("\nПоля одного цвета.\n");
				}
				else {
					printf("\nПоля разного цвета.\n");
				}
				current_status = 0;
			}
			break;

			// проверка на некорректный выбор номера задачи
		default:
			printf("Проверьте корректность введённых данных.\n");

		}

	}
	system("PAUSE");
	return 0;
}