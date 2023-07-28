#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Delivery;
class Letter1;

// класс ФИО
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

    char* getSurname() {
        return surname;
    }
    char* getName() {
        return name;
    }
    char* getPatronymic() {
        return patronymic;
    }

};

// класс даты
class Date {

    friend istream& operator >> (istream& is, Date& date);

    int day;
    int month;
    int year;

public:

    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date() {
        day = 1;
        month = 1;
        year = 1970;
    }

    int getDay() {
        return day;
    }

    int getMonth() {
        return month;
    }

    int getYear() {
        return year;
    }

    void setDay(int day) {
        this->day = day;
    }

    void setMonth(int month) {
        this->month = month;
    }

    void setYear(int year) {
        this->year = year;
    }

};

// функция разделения строки по символу
vector <string> split(string strToSplit, char delimeter) {
    stringstream ss(strToSplit);
    string item;
    vector < string > splittedStrings;
    while (getline(ss, item, delimeter)) {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}
// ошибка неверного формата даты
class DateFormatException {
public: DateFormatException() {}
};
// ошибка неверных символов даты
class DateSymbolsException {
public: DateSymbolsException() {}
};
// ошибка невозможного числа дня даты
class DayException {
public: DayException() {}
};
// ошибка невозможного числа месяца даты
class MonthException {
public: MonthException() {}
};
// ошибка невозможной даты в феврале
class FebruaryException {
public: FebruaryException() {}
};
// ошибка невозможного числа года даты
class YearException {
public: YearException() {}
};



// перегрузка оператора ввода для даты
istream& operator >> (istream& is, Date& date) {
    string local_input;
    int day;
    int month;
    int year;

    try {
        is >> local_input;
        if (local_input.find_first_not_of("0123456789.") == std::string::npos) {
            vector < string > splitted = split(local_input, '.');
            if (splitted.size() == 3) {

                day = atoi(splitted[0].c_str());
                month = atoi(splitted[1].c_str());
                year = atoi(splitted[2].c_str());

                int leapYear = year % 4;

                if ((day < 1 || day > 31) || (day > 30 + month % 2)) {
                    throw DayException();
                }
                if (month < 1 || month > 12) {
                    throw MonthException();
                }
                if (year < 1000 || year >= 9999) {
                    throw YearException();
                }
                if (month == 2 && day > 29 - leapYear) {
                    throw FebruaryException();
                }
            }
            else {
                throw DateFormatException();
            }
        }
        else {
            throw DateSymbolsException();
        }

        date.setDay(day);
        date.setMonth(month);
        date.setYear(year);
    }
    catch (...) {
        cout << "\nВведёна неверная дата.\n";
    }
}

// класс почты
class PostOffice {

    friend void saveData(PostOffice myPostOffice);

public:
    Letter* letters;
    static int count;

    // конструктор почты
    PostOffice(Letter* letters) {
        this->letters = letters;
    }

    // конструктор почты по умолчанию
    PostOffice() {
        letters = NULL;
    }

    PostOffice operator!();

};

// класс письма
class Letter {

    string address;
    Fio receiver;
    double cost;

public:
    // конструктор письма for new letters
    Letter(string address, Fio receiver, double cost) {
        PostOffice::count++;
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

    // перегрузка оператора сравнения для получателя письма и ФИО
    bool operator == (Fio fio) {
        return ((strcmp(receiver.getSurname(), fio.getSurname()) == 0) && (strcmp(receiver.getName(), fio.getName()) == 0) && (strcmp(receiver.getPatronymic(), fio.getPatronymic()) == 0));
    }

    Fio getReceiver() {
        return receiver;
    }

    string getAddress() {
        return address;
    }

    double getCost() {
        return cost;
    }

};

// класс доставки
class Delivery {
public: Letter1* letters;
      static int count;

      // конструктор почты
      Delivery(Letter1* letters) {
          this->letters = letters;
      }

      // конструктор почты по умолчанию
      Delivery() {
          letters = NULL;
      }
};

// класс письма 1
class Letter1 {

    string address;
    Fio receiver;
    double cost;
    Date receiveDate;
    Fio postman;

public:
    Letter1(string address, Fio receiver, double cost, Date receiveDate, Fio postman) {
        Delivery::count++;
        this->address = address;
        this->receiver = receiver;
        this->cost = cost;
        this->receiveDate = receiveDate;
        this->postman = postman;
    }

    Letter1() {
        string defaultFio = "default";
        address = &defaultFio[0];
        receiver = Fio();
        cost = -1;
        receiveDate = Date();
        postman = Fio();
    }

    Date getReceiveDate() {
        return receiveDate;
    }

    Fio getPostman() {
        return postman;
    }

    void completeDelivery() {
        cout << "\n" << postman.getSurname() << " " << postman.getName() << " доставил письмо по адресу " << getAddress() << ".\n";
    }

    Fio getReceiver() {
        return receiver;
    }

    string getAddress() {
        return address;
    }

    double getCost() {
        return cost;
    }
};

// перегрузка оператора для сортировки по цене письма
PostOffice PostOffice::operator!() {

    Letter* sortedArr = new Letter[PostOffice::count + 1];
    std::copy(letters, letters + PostOffice::count, sortedArr);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (sortedArr[j].getCost() > sortedArr[j + 1].getCost()) {
                swap(sortedArr[j], sortedArr[j + 1]);
            }
        }
    }
    return PostOffice(sortedArr);
}

// вывод списка писем
void printLetters(Letter* letters) {
    for (int i = 0; i < PostOffice::count; i++) {
        cout << "\nПисьмо №" << i + 1 << ":\n";
        cout << "Адрес: " << letters[i].getAddress() << endl;
        cout << "ФИО получателя: " << letters[i].getReceiver().getSurname() << " " << letters[i].getReceiver().getName() << " " << letters[i].getReceiver().getPatronymic() << endl;
        cout << "Цена письма: " << letters[i].getCost() << endl;
    }
}

// вывод списка писем в доставке
void printLettersDelivery(Letter1* letters) {
    for (int i = 0; i < Delivery::count; i++) {
        cout << "\nПисьмо №" << i + 1 << ":\n";
        cout << "Адрес: " << letters[i].getAddress() << endl;
        cout << "Почтальон: " << letters[i].getPostman().getSurname() << " " << letters[i].getPostman().getName() << " " << letters[i].getPostman().getPatronymic() << endl;
        cout << "Дата доставки: " << letters[i].getReceiveDate().getDay() << "." << letters[i].getReceiveDate().getMonth() << "." << letters[i].getReceiveDate().getYear() << endl;
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
    cout << "Распечатать информацию о письмах в доставке: ...........6" << endl;
    cout << "Найти письма с заданной датой вручения: ................7" << endl;
    cout << "Завершение сессии: .....................................0" << endl;
    SetConsoleTextAttribute(h, 15);
}

// поиск писем по адресу получателя
void findAddress(Letter* letters, string address) {
    bool flag = false;
    for (int i = 0; i < PostOffice::count; i++) {

        if (((letters[i].getAddress() == address))) {
            flag = true;
            cout << "\nПисьмо №" << i + 1 << ":\n";
            cout << "Адрес: " << letters[i].getAddress() << endl;
            cout << "ФИО получателя: " << letters[i].getReceiver().getSurname() << " " << letters[i].getReceiver().getName() << " " << letters[i].getReceiver().getPatronymic() << endl;
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
        out << myPostOffice.count << endl;
        // запись соответствующих параметров для каждого письма
        for (int i = 0; i < myPostOffice.count; i++) {
            out << myPostOffice.letters[i].getReceiver().getSurname() << endl;
            out << myPostOffice.letters[i].getReceiver().getName() << endl;
            out << myPostOffice.letters[i].getReceiver().getPatronymic() << endl;
            out << myPostOffice.letters[i].getAddress() << endl;
            out << myPostOffice.letters[i].getCost() << endl;

        }
    }
    out.close();
}

// добавление нового письма
Letter* addLetter(Letter* p_letters, string address, Fio fio, double cost) {

    // копирование всех старых писем в расширенный массив
    Letter* newArr = new Letter[PostOffice::count + 1];
    std::copy(p_letters, p_letters + min(PostOffice::count, PostOffice::count + 1), newArr);
    delete[] p_letters;
    p_letters = newArr;

    // добавление нового письма
    Letter newletter = Letter(address, fio, cost);
    p_letters[PostOffice::count - 1] = newletter;

    return p_letters;
}

// добавление нового письма в доставку
Letter1* addLetterDelivery(Letter1* p_letters, string address, Fio fio, double cost, Date date, Fio postman) {

    // копирование всех старых писем в расширенный массив
    Letter1* newArr = new Letter1[Delivery::count + 1];
    std::copy(p_letters, p_letters + min(Delivery::count, Delivery::count + 1), newArr);
    delete[] p_letters;
    p_letters = newArr;

    // добавление нового письма
    Letter1 newletter = Letter1(address, fio, cost, date, postman);
    p_letters[Delivery::count - 1] = newletter;

    return p_letters;
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

    Letter* letters = new Letter[PostOffice::count + 1];

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

        letters = addLetter(letters, address, localfio, cost);

    }

    // закрытие файла
    myfile.close();

    PostOffice::count = counter;
    return PostOffice(letters);
}

// загрузка данных с диска
Delivery loadDataDelivery() {

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

    Letter1* letters = new Letter1[Delivery::count + 1];

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

        Date sampleEstimatedDate = Date(10, 10, 2023);
        Date sample2EstimatedDate = Date(11, 10, 2023);
        Fio myPostman = Fio("Почтальонов", "Почтальон", "Почтальонович");

        if (Delivery::count == 1) {
            letters = addLetterDelivery(letters, address, localfio, cost, sample2EstimatedDate, myPostman);
        }
        else {
            letters = addLetterDelivery(letters, address, localfio, cost, sampleEstimatedDate, myPostman);
        }

    }

    // закрытие файла
    myfile.close();

    Delivery::count = counter;
    return Delivery(letters);
}

// поиск писем по ФИО получателя
void findFio(Letter* letters, Fio fio) {
    bool flag = false;
    for (int i = 0; i < PostOffice::count; i++) {
        if (letters[i] == fio) {
            flag = true;
            cout << "\nПисьмо №" << i + 1 << ":\n";
            cout << "Адрес: " << letters[i].getAddress() << endl;
            cout << "ФИО получателя: " << letters[i].getReceiver().getSurname() << " " << letters[i].getReceiver().getName() << " " << letters[i].getReceiver().getPatronymic() << endl;
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
    return s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ") != std::string::npos;
}

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) {
            return !std::isdigit(c);
        }) == s.end();
}

// проверка на дробное число
bool isNumber(const std::string& s) {
    long double ld;
    return ((std::istringstream(s) >> ld >> std::ws).eof());
}

int PostOffice::count = 0;
int Delivery::count = 0;

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
    Delivery myDelivery;

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
            myDelivery = loadDataDelivery();
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

        string curr_input;

        int firstEnterQ = 0;

        do {
            if (firstEnterQ != 0) {
                callError(h);
            }
            firstEnterQ = 1;
            cin >> curr_input;
        } while (is_number(curr_input) == 0 || (stoi(curr_input) > 7) || (stoi(curr_input) < 0));

        task_chosen = stoi(curr_input);

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
                myPostOffice.letters = addLetter(myPostOffice.letters, address, localfio, stringToDouble(input_cost));

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

                delete[] newPost.letters;
            }
            break;

            // печать информации о письмах в доставке
        case 6: {
            printLettersDelivery(myDelivery.letters);
            break;
        }

              // поиск письма в доставке по дате
        case 7: {
            SetConsoleTextAttribute(h, 3);
            cout << "\nВведите дату доставки для поиска в формате DD.MM.YYYY: ";
            SetConsoleTextAttribute(h, 15);

            Date dateToFind = Date();
            dateToFind.setDay(-1);

            // ввод даты, используя перегрузку оператора
            cin >> dateToFind;

            if (dateToFind.getDay() != -1) {
                bool flag = false;
                for (int i = 0; i < PostOffice::count; i++) {
                    if ((dateToFind.getDay() == myDelivery.letters[i].getReceiveDate().getDay()) && (dateToFind.getMonth() == myDelivery.letters[i].getReceiveDate().getMonth()) && (dateToFind.getYear() == myDelivery.letters[i].getReceiveDate().getYear())) {
                        flag = true;
                        cout << "\nПисьмо №" << i + 1 << ":\n";
                        cout << "Адрес: " << myDelivery.letters[i].getAddress() << endl;
                        cout << "ФИО получателя: " << myDelivery.letters[i].getReceiver().getSurname() << " " << myDelivery.letters[i].getReceiver().getName() << " " << myDelivery.letters[i].getReceiver().getPatronymic() << endl;
                        cout << "Цена письма: " << myDelivery.letters[i].getCost() << endl;
                    }
                }
                if (!flag) {
                    cout << "\nТаких писем нет.\n";
                }
            }
            break;
        }

              // проверка на некорректный выбор номера задачи
        default:
            SetConsoleTextAttribute(h, 4);
            printf("\nПроверьте корректность введённых данных.\n\n");
            SetConsoleTextAttribute(h, 15);
        }
    }

    // очистка динамической памяти
    delete[] myPostOffice.letters;
    delete[] myDelivery.letters;

    // установка исходных параметров кодировки
    SetConsoleCP(oldin);
    SetConsoleOutputCP(oldout);

    system("pause");
    return 0;

}