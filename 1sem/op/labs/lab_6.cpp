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
#include <windows.h>

using namespace std;

// максимальное количество счетов, поддерживаемых банком
#define DEPOSITS_MAX 50

// максимальная величина буфера
#define BUFFER_LENGTH 80

// структура банковского счёта
struct deposit {
    int number; // номер счета
    char* surname; // фамилия клиента 
    char* name; // имя клиента
    double balance; // сумма на счёте
};

// вывод информации о банковском счёте
void printAccount(struct deposit* account) {

    cout << "\nИнформация о счёте №" << account->number << ":\n";
    cout << "Фамилия клиента: " << account->surname << endl;
    cout << "Имя клиента: " << account->name << endl;
    cout << "Баланс счёта: " << account->balance << "$" << endl << endl;

}

// открытие нового банковского счёта
void openAccount(struct deposit* account, int number, double balance) {

    // установка параметров банковского счёта соответственно аргументам функции
    account->balance = balance;
    account->number = number;
}

// проверка наличия клиента банка с данными фамилией и именем
void findClients(struct deposit* account, int* arr, char* surname, char* name, int i) {

    // проверка совпадения данных с соответствующими параметрами банковского счёта 
    if (strcmp(surname, account->surname) == 0 && strcmp(name, account->name) == 0) {
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

    cout << "Система загружена. Начало работы банка. Выберите необходимую команду.\n\n";

    // основной цикл работы программы
    while (status) {
        SetConsoleTextAttribute(h, 2);
        cout << "Добавить новый счёт: ...................................1" << endl;
        cout << "Распечатать информацию о счёте: ........................2" << endl;
        cout << "Определить все счета с суммой, больше заданной: ........3" << endl;
        cout << "Найти все счета заданного клиента (имя + фамилия): .....4" << endl;
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
                deposits[deposits_counter].surname = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].surname, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "Введите имя: ";
                SetConsoleTextAttribute(h, 15);

                // считывание строки, вводимой пользователем
                cin >> buff;

                // установка имени клиента для нового банковского счета
                deposits[deposits_counter].name = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].name, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "Введите баланс: (десятичный разделитель - точка): ";
                SetConsoleTextAttribute(h, 15);

                // считывание баланса, вводимого пользователем
                double balance_input;
                cin >> balance_input;

                // создание указателя на новый банковский счёт
                struct deposit* p_deposit = &deposits[deposits_counter];

                // установка номера и баланса для нового банковского счёта
                openAccount(p_deposit, deposits_counter + 1, balance_input);
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
                int sum_to_look;
                cin >> sum_to_look;

                // переменная для вывода шапки таблицы - если подходящих счетов нет, то шапка не нужна
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    //сравнение баланса текущего банковского счёта с суммой, введенной пользователем
                    if (deposits[i].balance > sum_to_look) {
                        if (flag == 0) {
                            cout << "\n(Номер счёта, Фамилия, Имя, Баланс счёта)\n";
                        }
                        cout << "№" << i + 1 << " - " << deposits[i].surname << " " << deposits[i].name << ", " << deposits[i].balance << "$" << "\n";
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

                // массив статусов банковских счетов с искомыми фамилией и именем клиента
                int* arr = new int[deposits_counter];

                // заполнение массива статусов банковских счетов
                for (int i = 0; i < deposits_counter; i++) {

                    // создание указателя на текущий банковский счёт
                    struct deposit* p_deposit = &deposits[i];

                    // сравнение искомых фамилии и имени клиента с характеристикой текущего банковского счёта
                    findClients(p_deposit, arr, surname_to_find, name_to_find, i);
                }

                // переменная для вывода шапки таблицы - если подходящих счетов нет, то шапка не нужна
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    // вывод подходящих банковских счетов
                    if (arr[i] == 1) {
                        if (flag == 0) {
                            cout << "\nСчета клиента " << surname_to_find << " " << name_to_find << " (номер, баланс):\n";
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

            // проверка на некорректный выбор номера задачи
        default:
            SetConsoleTextAttribute(h, 4);
            printf("\nПроверьте корректность введённых данных.\n\n");
            SetConsoleTextAttribute(h, 15);
        }
    }

    // установка исходных параметров кодировки
    SetConsoleCP(oldin);
    SetConsoleOutputCP(oldout);

    system("pause");
    return 0;

}
/*
Created by SouthBoss at 2022
*/