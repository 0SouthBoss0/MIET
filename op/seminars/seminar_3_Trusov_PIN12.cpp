#include <stdio.h>
#include <clocale>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <cstring>
#include <time.h>

#define N 80
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

//нахождение суммы элементов последовательности, входящих в область жёлтого цвета
int sumOfYellowPart(int** matrix, int size) {
    int s = 0;

    for (int i = 0; i < size / 2 + 1; i++) {
        for (int j = 0; j < size / 2 + 1; j++) {
            if (i + j < size / 2 + 1) {
                s += matrix[i][j];;
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

//нахождение суммы элементов последовательности, входящих в область первой половины
int sumOfTopHalfPart(int** matrix, int size) {
    int s = 0;

    for (int i = 0; i < size / 2 + 1; i++) {
        for (int j = 0; j < size; j++) {
            s += matrix[i][j];
        }
    }

    return s;
}

//удаление самого длинного слова в строке
char* delete_long_word(char* str) {

    char* word;
    char* maxWord;
    char* delim = (char*) ".,:; ?!-()'[]{}";

    int len, maxlen;

    // копия строки
    char* strCopy = new char[strlen(str) + 1];
    strcpy(strCopy, str);

    // выделяем первое слово
    word = strtok(strCopy, delim);
    maxWord = word;
    maxlen = strlen(word);

    // пока есть слова
    while (word) {
        len = strlen(word);
        if (len > maxlen) {
            maxlen = len;
            maxWord = word;
        }
        
        // выделение очередного слова
        word = strtok(NULL, delim);
    }
    // нахождение самого длинного слова в строке
    word = strstr(str, maxWord);

    // удаление самого длинного слова в строке
    strcpy(word, word + maxlen);

    return str;
}

int main() {
    // сохранение исходных параметров кодировки
    int oldin = GetConsoleCP();
    int oldout = GetConsoleOutputCP();

    // установка необходимых параметров кодировки
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    // русификация текстов 
    setlocale(LC_ALL, "Russian");

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

                printf("\nЗадача 1.\nСоздать функцию для поиска положения первого нулевого элемента произвольного массива целых чисел.");
                printf("\nВернуть индекс нулевого элемента. Полученный индекс разделяет массив на две части.");
                printf("\nОпределить в какой части сумма элементов больше.\n");

                int size;
                printf("\nВведите размер массива: ");
                scanf_s("%d", &size);

                if (size <= 0) {
                    printf("Ошибка. Размер массива должен быть положительным.\n");
                    printf("Задача перезапущена.\n");
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

                    printf("Ошибка. В сгенерированном массиве нет нулевого элемента. Задача перезапущена.\n");

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

                printf("\nЗадача 2.\nСоздать функцию для удаления самого длинного слова в строке (возвращается измененная строка).\n");

                //буфер для ввода строки
                char buff[N] = {
                  "\0"
                };

                //статический массив указателей для адресации динамических строк
                char* din_str[N];
                int k = 0;

                // Ввод текста
                printf("Введите строку.\n");

                while (k != 2) {

                    // ввод строки в буфер
                    gets_s(buff);

                    // выделение динамической памяти под строку
                    din_str[k] = (char*)malloc(strlen(buff) + 1);

                    strcpy(din_str[k], buff);

                    k += 1;

                }
                delete_long_word(din_str[1]);
                printf("Строка с удаленным самым длинным словом: %s\n", din_str[1]);

                current_status = 0;
            }
            break;

            // задача 3
        case 3:
            current_status = 1;
            while (current_status) {

                printf("\nЗадача 3.\nДана целочисленная матрица NxN.");
                printf("\nНаписать пользовательскую функцию подсчета суммы в области синего цвета.");
                printf("\nМатрицу необходимо  объявить в динамической памяти.\n");

                int size;
                printf("\nВведите нечётное N: ");
                scanf_s("%d", &size);

                if (size % 2 == 0) {
                    printf("Ошибка. N должно быть нечётным, иначе невозможно построить область синего цвета в форме равнобедренного треугольника.\n");
                    printf("Задача перезапущена.\n");
                    continue;
                }
                if (size <= 0) {
                    printf("Ошибка. Число N должно быть нечётным и положительным.\n");
                    printf("Задача перезапущена.\n");
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

                //нахождение суммы элементов матрицы, входящих в область верхней половины
                int halfpart = sumOfTopHalfPart(Matr, size);

                //нахождение суммы элементов матрицы, входящих в область жёлтого цвета
                int greenPart = sumOfYellowPart(Matr, size);

                //нахождение суммы элементов матрицы, входящих в область синего цвета
                int answer = halfpart - greenPart;
                printf("\nСумма в области синего цвета: %d\n", answer);

                // очистка динамической памяти
                for (int w = 0; w < size; w++)
                    delete[] Matr[w];
                delete[] Matr;

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