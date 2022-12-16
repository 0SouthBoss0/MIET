/*
Created by SouthBoss at 2022
*/

/*
В случае если некорректно отображаются шрифты:

Запустите любое консольное приложение
Откройте меню, щелкнув по левому верхнему углу.
Умолчания / Шрифты
В шрифтах установите Lucida Console
Запустите проект заново.
*/

#include <iostream>
#include <string>
#include <locale>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <string.h>

using namespace std;

// максимальное количество счетов, поддерживаемых банком
#define DEPOSITS_MAX 50

// максимальная величина буфера
#define BUFFER_LENGTH 80

// структура ФИО
typedef struct fio {
    char* surname; // фамилия 
    char* name; // имя 
    char* patronymic; // отчество
};

// структура даты
typedef struct date {
    int day; // день 
    int month; // месяц 
    int year; // год
};

// структура банковского счёта
struct deposit {
    fio client; // ФИО клиента
    date creation_date; // дата открытия счёта
    int number; // номер счета
    double balance; // сумма на счёте
};

// загрузка данных с диска
void loadData(struct deposit* deposits, int* global_counter) {
    int counter;
    int number;
    double d_number;
    string s;

    // ввод из файла
    ifstream file("bank_data.txt");

    // количество открытых счетов
    getline(file, s);
    counter = std::stoi(s);
    (*global_counter) = counter;

    // цикл по всем счетам из файла
    for (int i = 0; i < counter; i++) {

        // номер счёта
        getline(file, s);
        number = std::stoi(s);
        deposits[i].number = number;

        // фамилия клиента
        getline(file, s);
        deposits[i].client.surname = new char[strlen(s.c_str()) + 1];
        strcpy(deposits[i].client.surname, s.c_str());

        // имя клиента
        getline(file, s);
        deposits[i].client.name = new char[strlen(s.c_str()) + 1];
        strcpy(deposits[i].client.name, s.c_str());

        // отчество клиента
        getline(file, s);
        deposits[i].client.patronymic = new char[strlen(s.c_str()) + 1];
        strcpy(deposits[i].client.patronymic, s.c_str());

        // день открытия счёта
        getline(file, s);
        number = std::stoi(s);
        deposits[i].creation_date.day = number;

        // месяц открытия счёта
        getline(file, s);
        number = std::stoi(s);
        deposits[i].creation_date.month = number;

        // год открытия счёта
        getline(file, s);
        number = std::stoi(s);
        deposits[i].creation_date.year = number;

        // баланс счёта
        getline(file, s);
        d_number = std::stod(s);
        deposits[i].balance = d_number;

    }

    // закрытие файла
    file.close();
}

// сохранение данных на диск
void saveData(struct deposit* deposits, int deposits_counter) {

    // открытие файла в режиме изменения
    FILE* file;
    file = fopen("bank_data.txt", "w");

    // запись количество открытых счетов первой строкой файла
    fprintf(file, "%d\n", deposits_counter);

    // цикл по всем открытым счетам - построчная запись данных в файл
    for (int i = 0; i < deposits_counter; i++) {
        fprintf(file, "%d\n", deposits[i].number);
        fprintf(file, "%s\n", deposits[i].client.surname);
        fprintf(file, "%s\n", deposits[i].client.name);
        fprintf(file, "%s\n", deposits[i].client.patronymic);
        fprintf(file, "%d\n", deposits[i].creation_date.day);
        fprintf(file, "%d\n", deposits[i].creation_date.month);
        fprintf(file, "%d\n", deposits[i].creation_date.year);
        fprintf(file, "%.2f\n", deposits[i].balance);
        printf("\n");
    }

    // закрытие файла
    fclose(file);
}

// вывод информации о банковском счёте
void printAccount(struct deposit* account) {
    cout << "\nИнформация о счёте №" << account->number << ":\n";
    cout << "Фамилия клиента: " << account->client.surname << endl;
    cout << "Имя клиента: " << account->client.name << endl;
    cout << "Отчество клиента: " << account->client.patronymic << endl;
    cout << "Дата открытия счёта: " << account->creation_date.day << "." << account->creation_date.month << "." << account->creation_date.year << endl;
    cout << "Баланс счёта: " << account->balance << "$" << endl << endl;
}

// проверка превосходства даты открытия счёта над датой
bool isBigger(int day_to_find, int month_to_find, int year_to_find, int day, int month, int year) {

    // введённый год превосходит год открытия счёта
    if (year_to_find > year) {
        return false;
    }

    // введённый год равен году открытия счёта
    if (year_to_find == year) {
        // введённый месяц превосходит месяц открытия счёта
        if (month_to_find > month) {
            return false;
        }
    }

    // введённый год равен году открытия счёта
    if (year_to_find == year) {
        // введённый месяц равен месяцу открытия счёта
        if (month_to_find == month) {
            // введённый день превосходит день открытия счёта
            if (day_to_find >= day) {
                return false;
            }
        }
    }

    // дата открытия счёта превосходит над датой
    return true;
}

// открытие нового банковского счёта
void openAccount(struct deposit* account, int number, double balance, int day, int month, int year) {

    // установка параметров банковского счёта соответственно аргументам функции
    account->balance = balance;
    account->number = number;
    account->creation_date.day = day;
    account->creation_date.month = month;
    account->creation_date.year = year;
}

// проверка наличия клиента банка с данными фамилией и именем
void findClients(struct deposit* account, int* arr, char* surname, char* name, char* patronymic, int i) {

    // проверка совпадения данных с соответствующими параметрами банковского счёта 
    if (strcmp(surname, account->client.surname) == 0 && strcmp(name, account->client.name) == 0 && strcmp(patronymic, account->client.patronymic) == 0) {
        *(arr + i) = 1;
    }
    else {
        *(arr + i) = 0;
    }
}

int main() {

    // сохранение исходных параметров кодировки
    int oldin = GetConsoleCP();
    int oldout = GetConsoleOutputCP();

    // установка необходимых параметров кодировки
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // русификация программы
    setlocale(LC_ALL, "Russian");

    // получение консольного окна для изменения цвета шрифта
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);

    // переменные, отвечающие за состояние и выход из циклов
    int status = 1;
    int current_status = 0;

    // счётчик текущего количества открытых банковских счетов
    int deposits_counter = 0;

    // массив банковских счетов
    struct deposit deposits[DEPOSITS_MAX];

    // открытие файла в режиме чтения 
    FILE* g;
    g = fopen("bank_data.txt", "r");

    // проверка существования файла
    if (g) {
        fseek(g, 0, SEEK_END);
        long pos = ftell(g);

        // проверка файла на пустоту
        if (pos > 2) {
            loadData(deposits, &deposits_counter);
        }
    }

    cout << "Система загружена. Начало работы банка. Выберите необходимую команду.\n\n";

    // основной цикл работы программы
    while (status) {
        SetConsoleTextAttribute(h, 2);
        cout << "Добавить новый счёт: ...................................1" << endl;
        cout << "Распечатать информацию о счёте: ........................2" << endl;
        cout << "Определить все счета с суммой, больше заданной: ........3" << endl;
        cout << "Найти все счета заданного клиента: .....................4" << endl;
        cout << "Найти все счета, открытые позже заданной даты: .........5" << endl;
        cout << "Завершение сессии: .....................................0" << endl;
        SetConsoleTextAttribute(h, 15);

        // считывание команды, выбранной пользователем
        int task_chosen;
        cin >> task_chosen;

        // переход к задаче, выбранной пользователем
        switch (task_chosen) {

            // завершение программы
        case 0:
            status = 0;
            printf("\nПрограмма завершена.\n");
            break;

            // добавление нового счёта
        case 1:
            current_status = 1;
            while (current_status) {

                // создание буфера 
                char buff[BUFFER_LENGTH];

                SetConsoleTextAttribute(h, 3);
                cout << "Введите фамилию: ";
                SetConsoleTextAttribute(h, 15);

                // считывание строки, вводимой пользователем
                cin >> buff;

                // установка фамилии клиента для нового банковского счета
                deposits[deposits_counter].client.surname = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].client.surname, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "Введите имя: ";
                SetConsoleTextAttribute(h, 15);

                // считывание строки, вводимой пользователем
                cin >> buff;

                // установка имени клиента для нового банковского счета
                deposits[deposits_counter].client.name = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].client.name, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "Введите отчество: ";
                SetConsoleTextAttribute(h, 15);

                // считывание строки, вводимой пользователем
                cin >> buff;

                // установка фамилии клиента для нового банковского счета
                deposits[deposits_counter].client.patronymic = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].client.patronymic, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "Введите баланс: (десятичный разделитель - точка): ";
                SetConsoleTextAttribute(h, 15);

                // считывание баланса, вводимого пользователем
                double balance_input;
                cin >> balance_input;

                struct date current_date;
                time_t now = time(0);
                tm* ltm = localtime(&now);

                current_date.day = ltm->tm_mday;
                current_date.month = 1 + ltm->tm_mon;
                current_date.year = 1900 + ltm->tm_year;

                // создание указателя на новый банковский счёт
                struct deposit* p_deposit = &deposits[deposits_counter];

                // установка номера и баланса для нового банковского счёта
                openAccount(p_deposit, deposits_counter + 1, balance_input, current_date.day, current_date.month, current_date.year);
                cout << "\nНомер открытого счёта: " << deposits_counter + 1 << "\n" << endl;

                // инкремент текущего количества открытых банковских счетов
                deposits_counter += 1;
                current_status = 0;
            }
            break;

            // печать информации о счёте
        case 2:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите номер счёта: ";
                SetConsoleTextAttribute(h, 15);

                // считывание номера банковского счёта, вводимого пользователем
                int deposit_index;
                cin >> deposit_index;

                // проверка валидности номера банковского счёта, введённого пользователем
                if (deposit_index > deposits_counter || deposit_index <= 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\nТакого счёта не существует. Проверьте номер.\n\n";
                    SetConsoleTextAttribute(h, 15);
                    break;
                }

                // создание указателя на текущий банковский счёт
                struct deposit* p_deposit = &deposits[deposit_index - 1];

                // вывод информации о текущем банковском счёте
                printAccount(p_deposit);

                current_status = 0;
            }
            break;

            // определение всех счетов с балансом, больше заданной пользователем суммы
        case 3:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите сумму для вывода счетов, баланс которых больше введенной: ";
                SetConsoleTextAttribute(h, 15);

                // считывание суммы, вводимой пользователем
                double sum_to_look;
                cin >> sum_to_look;

                // переменная для вывода шапки таблицы - если подходящих счетов нет, то шапка не нужна
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    //сравнение баланса текущего банковского счёта с суммой, введенной пользователем
                    if (deposits[i].balance > sum_to_look) {
                        if (flag == 0) {
                            cout << "\n(Номер счёта, Фамилия, Имя, Отчество, Баланс счёта)\n";
                        }
                        cout << "№" << i + 1 << " - " << deposits[i].client.surname << " " << deposits[i].client.name << " " << deposits[i].client.patronymic << ", " << deposits[i].balance << "$" << "\n";
                        flag = 1;
                    }
                }

                // если подходящих счетов нет
                if (flag == 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\nТаких счетов нет.\n";
                    SetConsoleTextAttribute(h, 15);
                }

                current_status = 0;
            }
            break;

            // поиск всех банковских счетов заданного пользователем клиента
        case 4:
            current_status = 1;
            while (current_status) {

                // создание буфера
                char buff[BUFFER_LENGTH];

                SetConsoleTextAttribute(h, 3);
                cout << "Введите фамилию искомого клиента: ";
                SetConsoleTextAttribute(h, 15);

                // считывание строки, вводимой пользователем
                cin >> buff;

                // сохранение фамилии клиента для поиска банковских счетов
                char* surname_to_find;
                surname_to_find = new char[strlen(buff) + 1];
                strcpy(surname_to_find, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "Введите имя искомого клиента: ";
                SetConsoleTextAttribute(h, 15);

                // считывание строки, вводимой пользователем
                cin >> buff;

                // сохранение имени клиента для поиска банковских счетов
                char* name_to_find;
                name_to_find = new char[strlen(buff) + 1];
                strcpy(name_to_find, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "Введите отчество искомого клиента: ";
                SetConsoleTextAttribute(h, 15);

                // считывание строки, вводимой пользователем
                cin >> buff;

                // сохранение имени клиента для поиска банковских счетов
                char* patronymic_to_find;
                patronymic_to_find = new char[strlen(buff) + 1];
                strcpy(patronymic_to_find, buff);

                // массив статусов банковских счетов с искомыми фамилией и именем клиента
                int* arr = new int[deposits_counter];

                // заполнение массива статусов банковских счетов
                for (int i = 0; i < deposits_counter; i++) {

                    // создание указателя на текущий банковский счёт
                    struct deposit* p_deposit = &deposits[i];

                    // сравнение искомых фамилии и имени клиента с характеристикой текущего банковского счёта
                    findClients(p_deposit, arr, surname_to_find, name_to_find, patronymic_to_find, i);
                }

                // переменная для вывода шапки таблицы - если подходящих счетов нет, то шапка не нужна
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    // вывод подходящих банковских счетов
                    if (arr[i] == 1) {
                        if (flag == 0) {
                            cout << "\nСчета клиента " << surname_to_find << " " << name_to_find << " " << patronymic_to_find << " (номер, баланс):\n";
                        }
                        cout << "№" << i + 1 << " - " << deposits[i].balance << "$" << "\n";

                        flag = 1;
                    }
                }

                // если подходящих счетов нет
                if (flag == 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\nТакого клиента нет.\n\n";
                    SetConsoleTextAttribute(h, 15);
                }

                // очистка динамической памяти
                delete[] arr;

                current_status = 0;
            }
            break;
            // печать информации о счёте
            // определение всех счетов, открытых позже заданной пользователем даты
        case 5:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите дату (DD.MM.YYYY) для вывода счетов, открытых позже заданной: ";
                SetConsoleTextAttribute(h, 15);

                // создание буфера 
                char buff[BUFFER_LENGTH];
                // считывание даты, вводимой пользователем
                cin >> buff;

                // сохранение даты, введённой пользователем
                char* date_to_find;
                date_to_find = new char[strlen(buff) + 1];
                strcpy(date_to_find, buff);

                // разделитель строки даты
                char sep[10] = ".";

                // Переменная, в которую будут заноситься начальные адреса частей строки
                char* istr;

                int day_to_find;
                int month_to_find;
                int year_to_find;

                // Выделение первой части строки (день)
                istr = strtok(date_to_find, sep);
                day_to_find = atoi(istr);

                // Выделение очередной части строки (месяц)
                istr = strtok(NULL, sep);
                month_to_find = atoi(istr);

                // Выделение очередной части строки (год)
                istr = strtok(NULL, sep);
                year_to_find = atoi(istr);

                // переменная для вывода шапки таблицы - если подходящих счетов нет, то шапка не нужна
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    //сравнение даты открытия текущего банковского счёта с датой, введенной пользователем
                    if (isBigger(day_to_find, month_to_find, year_to_find, deposits[i].creation_date.day, deposits[i].creation_date.month, deposits[i].creation_date.year)) {
                        if (flag == 0) {
                            cout << "\n(Номер счёта, Фамилия, Имя, Отчество, Дата открытия, Баланс счёта)\n";
                        }
                        cout << "№" << i + 1 << " - " << deposits[i].client.surname << " " << deposits[i].client.name << " " << deposits[i].client.patronymic << ", " << deposits[i].creation_date.day << "." << deposits[i].creation_date.month << "." << deposits[i].creation_date.year << ", " << deposits[i].balance << "$" << "\n";
                        flag = 1;
                    }
                }

                // если подходящих счетов нет
                if (flag == 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\nТаких счетов нет.\n\n";
                    SetConsoleTextAttribute(h, 15);
                }
                current_status = 0;
            }
            break;

            // проверка на некорректный выбор номера задачи
        default:
            SetConsoleTextAttribute(h, 4);
            printf("\nПроверьте корректность введённых данных.\n\n");
            SetConsoleTextAttribute(h, 15);
        }
    }

    // сохранение данных об открытых счетах
    saveData(deposits, deposits_counter);

    // установка исходных параметров кодировки
    SetConsoleCP(oldin);
    SetConsoleOutputCP(oldout);

    system("pause");
    return 0;
}
/*
Created by SouthBoss at 2022
*/