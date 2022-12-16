#include <iostream>
#include <iomanip>
#include <cstring>
#include <windows.h>
#define N 80
using namespace std;

//слов в строке
int scount(char* p) {
    int word, count = 0, i = 0;
    while (p[i] == ' ' && p[i] != '\0') {
        i++;
    }
    word = 0;
    while (p[i] != '\0') {
        if (p[i] != ' ' && word == 0) {
            word = 1;
            count++;
        }
        else if (p[i] == ' ')
            word = 0;
        i++;
    }
    return count;
}

//подсчёт параметров строки
void results(char* s, int i, int* arr) {
    char* pstr;
    int cntrls = 0, spaces = 0, digits = 0;
    pstr = s;
    for (; *pstr; pstr++) {
        if (isdigit(*pstr)) {
            digits++;
        }
        if (isspace(*pstr)) {
            spaces++;
        }
        if (iscntrl(*pstr)) {
            cntrls++;
        }

    }
    *(arr + 4 * i) = scount(s); //слов
    *(arr + (4 * i) + 1) = digits; //цифр
    *(arr + (4 * i) + 2) = spaces; //пробелов
    *(arr + (4 * i) + 3) = cntrls; //управляющих символов
}

int main() {
    setlocale(0,"Russian");

    //получаем окно в консоли, в котором будем изменять цвет
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);

    //буфер для ввода строки
    char buff[N] = {
      "\0"
    }, ending[N] = {
      "and"
    };

    //статический массив указателей для адресации динамических строк
    char* din_str[N];
    int k = 0;

    // Ввод текста
    SetConsoleTextAttribute(h, 2);
    cout << "Введите строки. Признак окончания – слово 'and'" << endl;
    SetConsoleTextAttribute(h, 15);

    while (strcmp(ending, buff)) {

        // ввод строки в буфер
        gets_s(buff);

        if (strcmp(ending, buff) != 0) {

            // выделение динамической памяти под строку
            din_str[k] = (char*)malloc(strlen(buff) + 1);

            strcpy(din_str[k], buff);
            k += 1;
        }
    }

    // Сортировка по увеличению количества слов
    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k; j++)
            if (scount(din_str[i]) > scount(din_str[j])) {
                char* temp = din_str[i];
                din_str[i] = din_str[j];
                din_str[j] = temp;
            }

    // Формирование массива результатов
    int* arr = new int[4 * k];
    for (int i = 0; i < k; i++)
        results(din_str[i], i, arr);

    // Вывод отсортированных строк c параметрами
    SetConsoleTextAttribute(h, 2);
    cout << "Отсортированные строки с параметрами:" << endl;
    cout << "(Слов; Цифр; Пробелов; Управляющих символов)" << endl;
    cout << endl;
    SetConsoleTextAttribute(h, 15);

    for (int i = 0; i < k; i++) {
        cout << i + 1 << ": ";
        SetConsoleTextAttribute(h, 2);
        cout << din_str[i];
        SetConsoleTextAttribute(h, 15);

        cout << " (";
        cout << *(arr + (4 * i) + 0) << " ";
        cout << *(arr + (4 * i) + 1) << " ";
        cout << *(arr + (4 * i) + 2) << " ";
        cout << *(arr + (4 * i) + 3) << "";
        cout << ")" << endl;
    }

    system("pause");
    return 0;
}