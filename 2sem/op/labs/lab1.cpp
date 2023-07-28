#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

// структура врача
struct doctor {

    char* fio; // ФИО врача
    int specialty; // специальность
    int qualification; //квалификация

};

// регистрация нового врача
void addDoctor(struct doctor* p_doctor, int number, string surname, string name, string patronymic, int p_specialty, int p_qualification) {

    // формирование ФИО нового врача
    string p_fio = (surname + " " + name + " " + patronymic);
    char* p_fio2 = new char[p_fio.length() + 1];
    strcpy(p_fio2, p_fio.c_str());

    // установка параметров для нового врача
    p_doctor->fio = p_fio2;
    p_doctor->specialty = p_specialty;
    p_doctor->qualification = p_qualification;

}

// поиск врача по заданному ФИО
void findDoctor(struct doctor* p_doctor, int* arr, string surname, string name, string patronymic, int i) {

    // формирование заданного ФИО
    string p_fio = (surname + " " + name + " " + patronymic);
    char* p_fio2 = new char[p_fio.length() + 1];
    strcpy(p_fio2, p_fio.c_str());

    // проверка совпадения данных с соответствующими параметрами врача
    if (strcmp(p_fio2, p_doctor->fio) == 0) {
        *(arr + i) = 1;
    }
    else {
        *(arr + i) = 0;
    }
}

// расшифровка кода специальности
string specialityName(int n) {
    switch (n) {
    case 1:
        return "терапевт";
        break;

    case 2:
        return "кардиолог";
        break;

    case 3:
        return "стоматолог";
        break;

    default:
        return "Speciality not found";

    }

}

// расшифровка кода квалификации
string qualificationName(int n) {
    switch (n) {
    case 0:
        return "высшая квалификация";
        break;

    case 1:
        return "первая квалификация";
        break;

    case 2:
        return "вторая квалицикация";
        break;

    default:
        return "Qualification not found";

    }

}

// сортировка ФИО по алфавиту
void sortAlpha(string* fios, int* numbers, int length) {

    string temp;
    int temp2;

    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - 1; j++) {
            if (fios[j] > fios[j + 1]) {

                temp = fios[j];
                fios[j] = fios[j + 1];
                fios[j + 1] = temp;

                temp2 = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp2;

            }
        }
    }

}

// сохранение данных на диске
void saveData(struct doctor* doctors, int number) {

    // поток для записи
    ofstream out;
    out.open("hospital_data.txt");
    if (out.is_open()) {
        // запись количества врачей первой строкой
        out << number << endl;

        // запись соответствующих параметров для каждого врача
        for (int i = 0; i < number; i++) {
            out << doctors[i].fio << endl;
            out << doctors[i].specialty << endl;
            out << doctors[i].qualification << endl;
        }
    }

}

// загрузка данных с диска
doctor* loadData(int* number) {

    ifstream myfile;
    myfile.open("hospital_data.txt");

    string s;
    int counter;
    int value;

    // чтение количества врачей
    getline(myfile, s);
    counter = std::stoi(s);
    *number = counter;
    
    doctor* doctors = new doctor[counter];

    // цикл по всем врачам из файла
    for (int i = 0; i < counter; i++) {

        getline(myfile, s);
        doctors[i].fio = new char[strlen(s.c_str()) + 1];
        strcpy(doctors[i].fio, s.c_str());

        getline(myfile, s);
        value = std::stoi(s);
        doctors[i].specialty = value;

        getline(myfile, s);
        value = std::stoi(s);
        doctors[i].qualification = value;

    }

    // закрытие файла
    myfile.close();
    return doctors;
}

// вывод главного меню программы
void callMenu(HANDLE h) {
    SetConsoleTextAttribute(h, 2);
    cout << endl;
    cout << "Добавить нового врача: .................................1" << endl;
    cout << "Распечатать информацию о врачах: .......................2" << endl;
    cout << "Поиск врача по ФИО: ....................................3" << endl;
    cout << "Фильтр по квалификации и специальности: ................4" << endl;
    cout << "Сортировать по алфавиту: ...............................5" << endl;
    cout << "Завершение сессии: .....................................0" << endl;
    SetConsoleTextAttribute(h, 15);
}

// вывод сообщения об ошибке
void callError(HANDLE h) {
    SetConsoleTextAttribute(h, 4);
    cout << "\nОшибка! Проверьте корректность ввода.\n";
    SetConsoleTextAttribute(h, 15);
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

    // счётчик текущего количества врачей
    static int doctors_counter = 0;

    // массив докторов
    doctor* doctors = new doctor[doctors_counter];

    // открытие файла в режиме чтения 
    FILE* g;
    g = fopen("hospital_data.txt", "r");

    // проверка существования файла
    if (g) {
        fseek(g, 0, SEEK_END);
        long pos = ftell(g);

        // проверка файла на пустоту
        if (pos > 2) {
            fclose(g);
            doctors = loadData(&doctors_counter);
        }
    }

    cout << "Система загружена. Выберите необходимую команду.\n";

    // основной цикл работы программы
    while (status) {

        callMenu(h);

        // считывание команды, выбранной пользователем
        int task_chosen;

        // проверка на корректность ввода
        while (!(cin >> task_chosen) || (task_chosen > 5) || (task_chosen < 0)) {

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
            saveData(doctors, doctors_counter);
            cout << "\nПрограмма завершена." << endl;
            break;

            // добавление нового врача
        case 1:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите ФИО врача: ";
                SetConsoleTextAttribute(h, 15);

                string surname, name, patronymic;
                cin >> surname >> name >> patronymic;

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите специальность врача (1-терапевт, 2-кардиолог, 3-стоматолог): ";
                SetConsoleTextAttribute(h, 15);

                int p_speciality;

                // проверка на корректность ввода
                while (!(cin >> p_speciality) || (p_speciality > 3) || (p_speciality < 1)) {

                    callError(h);

                    SetConsoleTextAttribute(h, 3);
                    cout << "\nВведите специальность врача (1-терапевт, 2-кардиолог, 3-стоматолог): ";
                    SetConsoleTextAttribute(h, 15);

                    cin.clear();
                    cin.ignore(132, '\n');
                }

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите квалификацию врача (0-высшая, 1-первая, 2-вторая): ";
                SetConsoleTextAttribute(h, 15);

                int p_quality;

                // проверка на корректность ввода
                while (!(cin >> p_quality) || (p_quality > 2) || (p_quality < 0)) {

                    callError(h);

                    SetConsoleTextAttribute(h, 3);
                    cout << "\nВведите квалификацию врача (0-высшая, 1-первая, 2-вторая): ";
                    SetConsoleTextAttribute(h, 15);

                    cin.clear();
                    cin.ignore(132, '\n');
                }

                
                doctor* new_doctors = new doctor[doctors_counter+1];
                for (int i = 0; i < doctors_counter; i++) {
                    new_doctors[i].fio = doctors[i].fio;
                    new_doctors[i].specialty = doctors[i].specialty;
                    new_doctors[i].qualification = doctors[i].qualification;

                }

                doctors = new_doctors;
                

                // создание указателя на нового врача
                struct doctor* p_doctor = &doctors[doctors_counter];
                addDoctor(p_doctor, doctors_counter + 1, surname, name, patronymic, p_speciality, p_quality);

                doctors_counter += 1;
                current_status = 0;
            }
            break;

            // печать информации о врачах
        case 2:
            current_status = 1;
            while (current_status) {

                for (int i = 0; i < doctors_counter; i++) {
                    cout << "\nВрач №" << i + 1 << ":\n";
                    cout << "ФИО врача: " << doctors[i].fio << endl;
                    cout << "Специальность врача: " << specialityName(doctors[i].specialty) << endl;
                    cout << "Квалификация врача: " << qualificationName(doctors[i].qualification) << endl;
                }

                current_status = 0;
            }
            break;

            // поиск врача по ФИО
        case 3:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите ФИО искомого врача: ";
                SetConsoleTextAttribute(h, 15);

                string surname, name, patronymic;
                cin >> surname >> name >> patronymic;

                int* arr = new int[doctors_counter];

                // заполнение массива статусов врачей
                for (int i = 0; i < doctors_counter; i++) {

                    // создание указателя на текущего врача
                    struct doctor* p_doctor = &doctors[i];

                    // сравнение искомых ФИО врача с текущим
                    findDoctor(p_doctor, arr, surname, name, patronymic, i);
                }

                int flag = 0;
                cout << endl;
                for (int i = 0; i < doctors_counter; i++) {

                    // вывод подходящих врачей
                    if (arr[i] == 1) {
                        cout << "Врач " << surname << " " << name << " " << patronymic << ": " << specialityName(doctors[i].specialty) << ", " << qualificationName(doctors[i].qualification) << endl;
                        flag = 1;

                    }

                }

                // если подходящих врачей нет
                if (flag == 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "Такого врача нет.\n";
                    SetConsoleTextAttribute(h, 15);
                }

                // очистка динамической памяти
                delete[] arr;

                current_status = 0;
            }
            break;

            // фильтр по квалификации и специальности
        case 4:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\nВыберите фильтр по специальности врача." << endl;
                cout << "(1-терапевт, 2-кардиолог, 3-стоматолог, 4-любая специальность): ";
                SetConsoleTextAttribute(h, 15);

                int speciality_filter;
                // проверка на корректность ввода
                while (!(cin >> speciality_filter) || (speciality_filter > 4) || (speciality_filter < 1)) {

                    callError(h);

                    SetConsoleTextAttribute(h, 3);
                    cout << "\nВыберите фильтр по специальности врача." << endl;
                    cout << "(1-терапевт, 2-кардиолог, 3-стоматолог, 4-любая специальность): ";
                    SetConsoleTextAttribute(h, 15);

                    cin.clear();
                    cin.ignore(132, '\n');
                }


                SetConsoleTextAttribute(h, 3);
                cout << "\nВыберите фильтр по квалификации врача." << endl;
                cout << "(0-высшая, 1-первая, 2-вторая, 3-любая квалификация): ";
                SetConsoleTextAttribute(h, 15);

                int qualification_filter;
                while (!(cin >> qualification_filter) || (qualification_filter > 3) || (qualification_filter < 0)) {

                    callError(h);

                    SetConsoleTextAttribute(h, 3);
                    cout << "\nВыберите фильтр по квалификации врача." << endl;
                    cout << "(0-высшая, 1-первая, 2-вторая, 3-любая квалификация): ";
                    SetConsoleTextAttribute(h, 15);

                    cin.clear();
                    cin.ignore(132, '\n');
                }

                int flag = 0;

                for (int i = 0; i < doctors_counter; i++) {

                    // вывод подходящих врачей
                    if (((doctors[i].specialty == speciality_filter) || (speciality_filter == 4)) && ((doctors[i].qualification == qualification_filter) || (qualification_filter == 3))) {
                        cout << "\nВрач " << doctors[i].fio << ": " << specialityName(doctors[i].specialty) << ", " << qualificationName(doctors[i].qualification);
                        flag = 1;

                    }

                }


                // если подходящих врачей нет
                if (flag == 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\nТакого врача нет.";
                    SetConsoleTextAttribute(h, 15);
                }
                cout << endl;
                current_status = 0;
            }
            break;

            // сортировка по алфавиту
        case 5:
            current_status = 1;
            while (current_status) {

                string* fios = new string[doctors_counter];
                int* numbers = new int[doctors_counter];

                for (int i = 0; i < doctors_counter; i++) {
                    fios[i] = doctors[i].fio;
                    numbers[i] = i;
                }

                sortAlpha(fios, numbers, doctors_counter);

                for (int i = 0; i < doctors_counter; i++) {
                    cout << "\nВрач " << fios[i] << ": " << specialityName(doctors[numbers[i]].specialty) << ", " << qualificationName(doctors[numbers[i]].qualification);

                }
                cout << endl;
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

    for (int i = 0; i < doctors_counter; i++) {
        delete[] doctors[i].fio;
    }
    
    delete[] doctors;
    

    system("pause");
    return 0;

}
