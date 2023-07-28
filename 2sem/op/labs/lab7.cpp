#include <windows.h>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/// класс ФИО
class Fio {
    char* surname;
    char* name;
    char* patronymic;
    friend class Letter;

public:
    // конструктор ФИО для символов
    Fio(char* p_surname, char* p_name, char* p_patronymic) {
        surname = p_surname;
        name = p_name;
        patronymic = p_patronymic;
    }

    // конструктор ФИО для строк
    Fio(string p_surname, string p_name, string p_patronymic) {
        char* p_surname2 = new char[p_surname.length() + 1];
        strcpy(p_surname2, p_surname.c_str());
        surname = p_surname2;

        char* p_name2 = new char[p_name.length() + 1];
        strcpy(p_name2, p_name.c_str());
        name = p_name2;

        char* p_patronymic2 = new char[p_patronymic.length() + 1];
        strcpy(p_patronymic2, p_patronymic.c_str());
        patronymic = p_patronymic2;
    }

    // конструктор ФИО по умолчанию
    Fio() {
        string defaultFio = "default";
        surname = &defaultFio[0];
        name = &defaultFio[0];
        patronymic = &defaultFio[0];
    }

    // конструктор копирования
    Fio(const Fio& f) {
        surname = f.surname;
        name = f.name;
        patronymic = f.patronymic;
    }

    char* getSurname() { return surname; }
    char* getName() { return name; }
    char* getPatronymic() { return patronymic; }
};

// класс письма
class Letter {
    string address;
    Fio receiver;
    double cost;

public:
    // конструктор письма
    Letter(string address, Fio receiver, double cost) {
        this->address = address;
        this->receiver = receiver;
        this->cost = cost;
    }

    // конструктор письма по умолчанию
    Letter() {
        string defaultFio = "default";
        address = &defaultFio[0];
        receiver = Fio();
        cost = -1;
    }

    // перегрузка оператора срвнения для получателя письма и ФИО
    bool operator==(Fio fio) {
        return ((strcmp(receiver.getSurname(), fio.getSurname()) == 0) && (strcmp(receiver.getName(), fio.getName()) == 0) &&
            (strcmp(receiver.getPatronymic(), fio.getPatronymic()) == 0));
    }

    Fio getReceiver() { return receiver; }

    string getAddress() { return address; }

    double getCost() { return cost; }

    friend ostream& operator<<(ostream& out, Letter& letter);
};

// перегрузка оператора вывода
ostream& operator<<(ostream& out, Letter& letter) {
    cout << "Адрес: " << letter.getAddress() << endl;
    cout << "ФИО получателя: " << letter.getReceiver().getSurname() << " " << letter.getReceiver().getName() << " "
        << letter.getReceiver().getPatronymic() << endl;
    cout << "Цена письма: " << letter.getCost() << endl;
    return out;
}

// класс почты
class PostOffice {
    friend void saveData(PostOffice myPostOffice);
public:
    deque<Letter> letters;
    // конструктор почты
    PostOffice(deque<Letter> letters) { this->letters = letters; }
    // конструктор почты по умолчанию
    PostOffice() {}
    PostOffice operator!();
};

// перегрузка оператора для сортировки по цене письма
PostOffice PostOffice::operator!() {
    deque<Letter> sortedArr = letters;
    for (int i = 0; i < sortedArr.size() - 1; i++) {
        for (int j = 0; j < sortedArr.size() - 1; j++) {
            if (sortedArr[j].getCost() > sortedArr[j + 1].getCost()) {
                swap(sortedArr[j], sortedArr[j + 1]);
            }
        }
    }
    return PostOffice(sortedArr);
}

// вывод списка писем
void printLetters(deque<Letter> letters) {
    for (int i = 0; i < letters.size(); i++) {
        cout << "\nПисьмо №" << i + 1 << ":\n";
        cout << letters[i];
    }
}

// конвертация строки в дробное число
double stringToDouble(const std::string& s) {
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

// вывод главного меню программы
void callMenu(HANDLE h) {
    SetConsoleTextAttribute(h, 2);
    cout << endl;
    cout << "Добавить новое письмо: .................................1" << endl;
    cout << "Распечатать информацию о письмах: ......................2" << endl;
    cout << "Поиск письма по адресу: ................................3" << endl;
    cout << "Поиск письма по ФИО: ...................................4" << endl;
    cout << "Сортировать письма по увеличению стоимости: ............5" << endl;
    cout << "Удалить последнее письмо из базы: ......................6" << endl;
    cout << "Завершение сессии: .....................................0" << endl;
    SetConsoleTextAttribute(h, 15);
}

// поиск писем по адресу получателя
void findAddress(deque<Letter> letters, string address) {
    bool flag = false;
    for (int i = 0; i < letters.size(); i++) {
        if (((letters[i].getAddress() == address))) {
            flag = true;
            cout << "\nПисьмо №" << i + 1 << ":\n";
            cout << "Адрес: " << letters[i].getAddress() << endl;
            cout << "ФИО получателя: " << letters[i].getReceiver().getSurname() << " " << letters[i].getReceiver().getName() << " "
                << letters[i].getReceiver().getPatronymic() << endl;
            cout << "Цена письма: " << letters[i].getCost() << endl;
        }
    }
    if (!flag) {
        cout << "\nТаких писем нет." << endl;
    }
}

// сохранение данных на диске
void saveData(PostOffice myPostOffice) {
    // поток для записи
    ofstream out;
    out.open("postOffice_data.txt.");
    if (out.is_open()) {
        // запись количества писем первой строкой
        out << myPostOffice.letters.size() << endl;
        // запись соответствующих параметров для каждого письма
        for (int i = 0; i < myPostOffice.letters.size(); i++) {
            out << myPostOffice.letters[i].getReceiver().getSurname() << endl;
            out << myPostOffice.letters[i].getReceiver().getName() << endl;
            out << myPostOffice.letters[i].getReceiver().getPatronymic() << endl;
            out << myPostOffice.letters[i].getAddress() << endl;
            out << myPostOffice.letters[i].getCost() << endl;
        }
    }
    out.close();
}

// загрузка данных с диска
PostOffice loadData() {
    ifstream myfile;
    myfile.open("postOffice_data.txt.");

    string s;
    string address;
    double cost;
    int counter;
    char* local_surname;
    char* local_name;
    char* local_patronymic;

    // чтение количества врачей
    getline(myfile, s);
    counter = stoi(s);

    deque<Letter> letters;

    // цикл по всем врачам из файла
    for (int i = 0; i < counter; i++) {
        getline(myfile, s);
        local_surname = new char[strlen(s.c_str()) + 1];
        strcpy(local_surname, s.c_str());

        getline(myfile, s);
        local_name = new char[strlen(s.c_str()) + 1];
        strcpy(local_name, s.c_str());

        getline(myfile, s);
        local_patronymic = new char[strlen(s.c_str()) + 1];
        strcpy(local_patronymic, s.c_str());

        Fio localfio = Fio(local_surname, local_name, local_patronymic);

        getline(myfile, address);

        getline(myfile, s);
        cost = stringToDouble(s);

        letters.push_back(Letter(address, localfio, cost));
    }

    // закрытие файла
    myfile.close();
    return PostOffice(letters);
}

// поиск писем по ФИО получателя
void findFio(deque<Letter> letters, Fio fio) {
    bool flag = false;
    for (int i = 0; i < letters.size(); i++) {
        if (letters[i] == fio) {
            flag = true;
            cout << "\nПисьмо №" << i + 1 << ":\n";
            cout << "Адрес: " << letters[i].getAddress() << endl;
            cout << "ФИО получателя: " << letters[i].getReceiver().getSurname() << " " << letters[i].getReceiver().getName() << " "
                << letters[i].getReceiver().getPatronymic() << endl;
            cout << "Цена письма: " << letters[i].getCost() << endl;
        }
    }
    if (!flag) {
        cout << "\nТаких писем нет.";
    }
}

// вывод сообщения об ошибке
void callError(HANDLE h) {
    SetConsoleTextAttribute(h, 4);
    cout << "\nОшибка! Проверьте корректность ввода.\n";
    SetConsoleTextAttribute(h, 15);
}

// проверка на наличие числа или спецсимвола в строке
bool isNonValid(string s) {
    return s.find_first_not_of(
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийкл"
        "мнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ") != std::string::npos;
}

// проверка на дробное число
bool isNumber(const std::string& s) {
    long double ld;
    return ((std::istringstream(s) >> ld >> std::ws).eof());
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

    PostOffice myPostOffice;

    // открытие файла в режиме чтения
    FILE* g;
    g = fopen("postOffice_data.txt", "r");

    // проверка существования файла
    if (g) {
        fseek(g, 0, SEEK_END);
        long pos = ftell(g);

        // проверка файла на пустоту
        if (pos > 2) {
            fclose(g);
            myPostOffice = loadData();
        }
    }

    // получение консольного окна для изменения цвета шрифта
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);

    // переменные, отвечающие за состояние и выход из циклов
    int status = 1;
    int current_status = 0;

    cout << "Система загружена. Выберите необходимую команду.\n";

    // основной цикл работы программы
    while (status) {
        callMenu(h);

        // считывание команды, выбранной пользователем
        int task_chosen;

        // проверка на корректность ввода
        while (!(cin >> task_chosen) || (task_chosen > 6) || (task_chosen < 0)) {
            callError(h);
            cin.clear();
            cin.ignore(132, '\n');
            callMenu(h);
        }

        // переход к задаче, выбранной пользователем
        switch (task_chosen) {
            // завершение программы
        case 0:

            status = 0;
            saveData(myPostOffice);
            cout << "\nПрограмма завершена." << endl;
            break;

            // добавление нового письма
        case 1:
            current_status = 1;
            while (current_status) {
                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите адрес получателя: ";
                SetConsoleTextAttribute(h, 15);

                string address;
                getline(cin, address);
                getline(cin, address);

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите ФИО получателя: ";
                SetConsoleTextAttribute(h, 15);

                string surname, name, patronymic;
                int firstEnter = 0;

                do {
                    if (firstEnter != 0) {
                        callError(h);
                    }
                    firstEnter = 1;
                    cin >> surname >> name >> patronymic;
                } while ((isNonValid(surname) + isNonValid(name) + isNonValid(patronymic)) != 0);

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите стоимость письма: ";
                SetConsoleTextAttribute(h, 15);

                string input_cost;

                firstEnter = 0;
                do {
                    if (firstEnter != 0) {
                        callError(h);
                    }
                    firstEnter = 1;
                    cin >> input_cost;

                    for (int i = 0; i < input_cost.length(); i++) {
                        if (input_cost[i] == ',') {
                            input_cost[i] = '.';
                        }
                    }
                } while (isNumber(input_cost) == 0);

                Fio localfio = Fio(surname, name, patronymic);

                myPostOffice.letters.push_back(Letter(address, localfio, stringToDouble(input_cost)));

                current_status = 0;
            }
            break;

            // печать информации о письмах
        case 2:
            current_status = 1;
            while (current_status) {
                printLetters(myPostOffice.letters);

                current_status = 0;
            }
            break;

            // поиск письма по адресу
        case 3:
            current_status = 1;
            while (current_status) {
                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите адрес искомого письма: ";
                SetConsoleTextAttribute(h, 15);

                string address_to_find;
                getline(cin, address_to_find);
                getline(cin, address_to_find);

                findAddress(myPostOffice.letters, address_to_find);

                current_status = 0;
            }
            break;

            // поиск письма по ФИО
        case 4:
            current_status = 1;
            while (current_status) {
                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите ФИО искомого получателя: ";
                SetConsoleTextAttribute(h, 15);

                string surname, name, patronymic;
                int firstEnter = 0;

                do {
                    if (firstEnter != 0) {
                        callError(h);
                    }
                    firstEnter = 1;
                    cin >> surname >> name >> patronymic;
                } while ((isNonValid(surname) + isNonValid(name) + isNonValid(patronymic)) != 0);

                Fio fioToFind = Fio(surname, name, patronymic);
                findFio(myPostOffice.letters, fioToFind);

                current_status = 0;
            }
            break;

            // сортировать письма по увеличению стоимости
        case 5:
            current_status = 1;
            while (current_status) {
                PostOffice newPost = !myPostOffice;
                printLetters(newPost.letters);
                current_status = 0;
            }
            break;
           // udalenie poslednego elementa iz bazi
        case 6:
            current_status = 1;
            while (current_status) {
                if (myPostOffice.letters.size() != 0) {
                    myPostOffice.letters.pop_back();
                    cout << "\nПоследнее письмо из базы удалено.\n";
                }
                else {
                    callError(h);
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

    // установка исходных параметров кодировки
    SetConsoleCP(oldin);
    SetConsoleOutputCP(oldout);

    system("pause");
    return 0;
}