#include <stdio.h>
#include <clocale>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <time.h>

//вывод массива
void printArray(int* array, int size) {
    printf("\nМассив:\n");
    for (int i = 0; i < size; i++) {
        printf("%d \t", array[i]);
    }
    printf("\n");
}

//вывод матрицы
void printMatrix(int** matrix, int size1, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            printf("%d \t", matrix[i][j]);
        }
        printf("\n");
    }
}

//нахождение индекса первого нулевого элемента массива
int findFirstZeroIndex(int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == 0) {
            return i;
        }
    }
    return -1;
}

//нахождение суммы четных элементов последовательности
int sumOfEvenFib(int* array, int size) {
    int s = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0) {
            s += array[i];
        }
    }
    return s;
}

//нахождение суммы элементов последовательности, входящих в область синего цвета
int sumOfBluePart(int** matrix, int size) {
    int s = 0;

    for (int i = 0; i < size / 2 + 1; i++) {
        for (int j = 0; j < size / 2 + 1; j++) {
            if (i + j < size / 2 + 1) {
                s += matrix[i][j];
            }
        }
    }
    for (int i = 0; i < size / 2 + 1; i++) {
        for (int j = size / 2 + 1; j < size; j++) {
            if (i + (size - j - 1) < size / 2 + 1) {
                s += matrix[i][j];
            }
        }
    }
    return s;
}

int main() {

    // русификация текстов 
    setlocale(LC_ALL, "Russian");

    //получаем окно в консоли, в котором будем изменять цвет
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 15);

    time_t k;
    srand(time(&k));

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
                SetConsoleTextAttribute(h, 2);
                printf("\nЗадача 1.\nСоздать функцию для поиска положения первого нулевого элемента произвольного массива целых чисел.");
                printf("\nВернуть индекс нулевого элемента. Полученный индекс разделяет массив на две части.");
                printf("\nОпределить в какой части сумма элементов больше.\n");
                SetConsoleTextAttribute(h, 15);

                int size;
                printf("\nВведите размер массива: ");
                scanf_s("%d", &size);

                if (size <= 0) {
                    SetConsoleTextAttribute(h, 4);
                    printf("Ошибка. Размер массива должен быть положительным.\n");
                    printf("Задача перезапущена.\n");
                    SetConsoleTextAttribute(h, 15);
                    continue;
                }

                //инициализация массива
                int* array;
                array = new int[size];

                //заполнение массива
                for (int i = 0; i < size; i++) {
                    array[i] = (rand() % 5) * pow(-1.0, rand());
                }

                //вывод массива
                printArray(array, size);

                //нахождение индекса первого нулевого элемента массива
                int z_index = findFirstZeroIndex(array, size);

                if (z_index == -1) {
                    SetConsoleTextAttribute(h, 4);
                    printf("Ошибка. В сгенерированном массиве нет нулевого элемента. Задача перезапущена.\n");
                    SetConsoleTextAttribute(h, 15);
                    delete[] array;
                    continue;
                }
                printf("\nИндекс первого нулевого элемента: %d\n", z_index);

                //нахождение сумм первой и второй части массива соответственно
                int sum_1 = 0;
                int sum_2 = 0;

                for (int i = 0; i < size; i++) {
                    if (i <= z_index) {
                        sum_1 += array[i];
                    }
                    else {
                        sum_2 += array[i];
                    }
                }

                if (sum_1 > sum_2) {
                    printf("\nСумма элементов больше в первой части массива.\n");
                }
                else {
                    if (sum_1 == sum_2) {
                        printf("\nСумма элементов в обоих частях массива равна.\n");
                    }
                    else {
                        printf("\nСумма элементов больше во второй части массива.\n");
                    }
                }
                delete[] array;
                current_status = 0;
            }
            break;

            // задача 2
        case 2:
            current_status = 1;
            while (current_status) {
                SetConsoleTextAttribute(h, 2);
                printf("\nЗадача 2.\nМассив А состоит из первых 15 элементов последовательности Фибоначчи.");
                printf("\nНаписать функцию подсчета суммы четных элементов последовательности.");
                printf("\nНа экран вывести массив и искомую сумму.\n");
                SetConsoleTextAttribute(h, 15);

                //инициализация массива
                int size = 15;
                int* array;
                array = new int[size];

                //первые два элемента последовательности Фибоначчи
                array[0] = 0;
                array[1] = 1;

                //нахождение последующих элементов последовательности Фибоначчи
                for (int i = 2; i < size; i++) {
                    array[i] = array[i - 2] + array[i - 1];
                }

                //вывод массива
                printArray(array, size);

                //нахождение суммы четных элементов последовательности
                int answer = sumOfEvenFib(array, size);

                printf("\nСумма четных элементов последовательности: %d\n", answer);

                delete[] array;
                current_status = 0;
            }
            break;

            // задача 3
        case 3:
            current_status = 1;
            while (current_status) {
                SetConsoleTextAttribute(h, 2);
                printf("\nЗадача 3.\nДана целочисленная матрица NxN.");
                printf("\nНаписать пользовательскую функцию подсчета суммы в области синего цвета.\n");
                SetConsoleTextAttribute(h, 15);

                int size;
                printf("\nВведите нечётное N: ");
                scanf_s("%d", &size);

                if (size % 2 == 0) {
                    SetConsoleTextAttribute(h, 4);
                    printf("Ошибка. N должно быть нечётным, иначе невозможно построить область синего цвета в форме равнобедренного треугольника.\n");
                    printf("Задача перезапущена.\n");
                    SetConsoleTextAttribute(h, 15);
                    continue;
                }
                if (size <= 0) {
                    SetConsoleTextAttribute(h, 4);
                    printf("Ошибка. Число N должно быть нечётным и положительным.\n");
                    printf("Задача перезапущена.\n");
                    SetConsoleTextAttribute(h, 15);
                    continue;
                }

                //инициализация матрицы
                int** Matr = new int* [size];
                for (int i = 0; i < size; i++)
                    Matr[i] = new int[size];

                //заполнение матрицы
                for (int i = 0; i < size; i++)
                    for (int j = 0; j < size; j++)
                        Matr[i][j] = (rand() % 100) * pow(-1.0, rand());

                //вывод матрицы
                printMatrix(Matr, size, size);

                //нахождение суммы элементов последовательности, входящих в область синего цвета
                int answer = sumOfBluePart(Matr, size);
                printf("\nСумма в области синего цвета: %d\n", answer);

                for (int w = 0; w < size; w++)
                    delete[] Matr[w];
                delete[] Matr;

                current_status = 0;
            }
            break;

            // проверка на некорректный выбор номера задачи
        default:
            SetConsoleTextAttribute(h, 4);
            printf("Проверьте корректность введённых данных.\n");
            SetConsoleTextAttribute(h, 15);
        }
    }
    system("PAUSE");
    return 0;
}