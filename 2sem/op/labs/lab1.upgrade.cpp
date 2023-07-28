#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

// структура врача
struct doctor {
    char* fio; // ФИО врача
    int specialty; // специальность
    int qualification; // квалификация
};

// регистрация нового врача
void addDoctor(struct doctor* p_doctor, int number, doctor d) {
    // установка параметров для нового врача
    p_doctor->fio = d.fio;
    p_doctor->specialty = d.specialty;
    p_doctor->qualification = d.qualification;
}

// поиск врача по заданному ФИО
void findDoctor(struct doctor* p_doctor, int* arr, char* fio, int i) {
    // проверка совпадения данных с соответствующими параметрами врача
    if (strcmp(fio, p_doctor->fio) == 0) {
        *(arr + i) = 1;
    }
    else {
        *(arr + i) = 0;
    }
}

// расшифровка кода специальности
char* specialityName(int n) {
    char sp1[] = "терапевт";
    char sp2[] = "кардиолог";
    char sp3[] = "стоматолог";
    char sp0[] = "Speciality not found";
    switch (n) {
    case 1:
        return sp1;
        break;

    case 2:
        return sp2;
        break;

    case 3:
        return sp3;
        break;

    default:
        return sp0;
    }
}

// расшифровка кода квалификации
char* qualificationName(int n) {
    char sp1[] = "высшая квалификация";
    char sp2[] = "первая квалификация";
    char sp3[] = "вторая квалицикация";
    char sp0[] = "Qualification not found";
    switch (n) {
    case 0:
        return sp1;
        break;

    case 1:
        return sp2;
        break;

    case 2:
        return sp3;
        break;

    default:
        return sp0;
    }
}

// сортировка ФИО по алфавиту
doctor* sortAlpha(doctor* doctors, int doctors_counter) {
    doctor* sortedDoc = new doctor[doctors_counter];

    // копирование докторов в новый массив
    for (int i = 0; i < doctors_counter; i++) {
        sortedDoc[i] = doctors[i];
    }

    // сортировка пузырьком
    for (int i = 0; i < doctors_counter - 1; i++) {
        for (int j = i + 1; j < doctors_counter; j++) {
            if (strcmp(sortedDoc[i].fio, sortedDoc[j].fio) > 0) {
                swap(sortedDoc[i], sortedDoc[j]);
            }
        }
    }
    return sortedDoc;
}

// сохранение данных на диске
void saveData(struct doctor* doctors, int number) {
    // write to the file
    FILE* fp = fopen("hospital_data.txt", "w");
    for (int i = 0; i < number; i++) {
        fprintf(fp, "%s|%d|%d\n", doctors[i].fio, doctors[i].specialty,
            doctors[i].qualification);
    }
    fclose(fp);
}

// загрузка данных с диска
doctor* loadData(int* number) {
    int counter = 0;
    char buf[255];
    char* word;
    doctor* doctors = NULL;
    FILE* fp = fopen("hospital_data.txt", "r");
    while (fgets(buf, 255, fp) != NULL) {
        doctor d;
        word = strtok(buf, "|");
        d.fio = (char*)malloc(strlen(word) + 1);
        strcpy(d.fio, word);

        word = strtok(NULL, "|");
        d.specialty = atoi(word);

        word = strtok(NULL, "|");
        d.qualification = atoi(word);

        if (counter == 0) {
            doctors = (doctor*)malloc(sizeof(doctor));
        }
        else {
            doctors = (doctor*)realloc(doctors, sizeof(doctor) * (counter + 1));
        }
        doctors[counter] = d;
        counter++;
    }
    *number = counter;
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

int getCharSize(char* ptr) {

    int offset = 0;
    int count = 0;

    while (*(ptr + offset) != '\0') {
        ++count;
        ++offset;
    }
    return count;
}

// проверка валидности символа
bool checkValidSymbols(char fio) {
    char valid[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдеёжзийклмнопрст"
        "уфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ ";
    bool flag = false;
    for (int i = 0; i < getCharSize(valid); i++) {
        if (fio == valid[i]) {
            return true;
        }
    }
    return false;
}

// проверка валидности ФИО
bool checkValid(char* fio) {
    int spaces_counter = 0;
    for (int i = 0; i < getCharSize(fio); i++) {
        if (checkValidSymbols(fio[i]) == false) {
            return false;
        }

        if (fio[i] == ' ') {
            spaces_counter += 1;
        }
    }
    if (spaces_counter != 2) {
        return false;
    }
    return true;
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
    int doctors_counter = 0;

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
                doctor d;
                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите ФИО врача: ";
                SetConsoleTextAttribute(h, 15);

                char buf[255];

                while (fgetc(stdin) != '\n');
                gets_s(buf);
                d.fio = (char*)malloc(strlen(buf) + 1);
                strcpy(d.fio, buf);

                if (!checkValid(d.fio)) {
                    callError(h);
                    break;
                }

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите специальность врача (1-терапевт, 2-кардиолог, "
                    "3-стоматолог): ";
                SetConsoleTextAttribute(h, 15);

                int p_speciality;

                // проверка на корректность ввода
                while (!(cin >> p_speciality) || (p_speciality > 3) ||
                    (p_speciality < 1)) {
                    callError(h);

                    SetConsoleTextAttribute(h, 3);
                    cout << "\nВведите специальность врача (1-терапевт, 2-кардиолог, "
                        "3-стоматолог): ";
                    SetConsoleTextAttribute(h, 15);

                    cin.clear();
                    cin.ignore(132, '\n');
                }
                d.specialty = p_speciality;

                SetConsoleTextAttribute(h, 3);
                cout << "\nВведите квалификацию врача (0-высшая, 1-первая, "
                    "2-вторая): ";
                SetConsoleTextAttribute(h, 15);

                int p_quality;

                // проверка на корректность ввода
                while (!(cin >> p_quality) || (p_quality > 2) || (p_quality < 0)) {
                    callError(h);

                    SetConsoleTextAttribute(h, 3);
                    cout << "\nВведите квалификацию врача (0-высшая, 1-первая, "
                        "2-вторая): ";
                    SetConsoleTextAttribute(h, 15);

                    cin.clear();
                    cin.ignore(132, '\n');
                }
                d.qualification = p_quality;

                doctor* new_doctors = new doctor[doctors_counter + 1];
                for (int i = 0; i < doctors_counter; i++) {
                    new_doctors[i].fio = doctors[i].fio;
                    new_doctors[i].specialty = doctors[i].specialty;
                    new_doctors[i].qualification = doctors[i].qualification;
                }

                doctors = new_doctors;

                // создание указателя на нового врача
                struct doctor* p_doctor = &doctors[doctors_counter];
                addDoctor(p_doctor, doctors_counter + 1, d);

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
                    cout << "Специальность врача: " <<
                        specialityName(doctors[i].specialty) << endl;
                    cout << "Квалификация врача: " <<
                        qualificationName(doctors[i].qualification) << endl;
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

                doctor d;

                char buf[255];

                while (fgetc(stdin) != '\n');
                gets_s(buf);
                d.fio = (char*)malloc(strlen(buf) + 1);
                strcpy(d.fio, buf);

                if (!checkValid(d.fio)) {
                    callError(h);
                    break;
                }

                int* arr = new int[doctors_counter];

                // заполнение массива статусов врачей
                for (int i = 0; i < doctors_counter; i++) {
                    // создание указателя на текущего врача
                    struct doctor* p_doctor = &doctors[i];

                    // сравнение искомых ФИО врача с текущим
                    findDoctor(p_doctor, arr, d.fio, i);
                }

                int flag = 0;
                cout << endl;
                for (int i = 0; i < doctors_counter; i++) {
                    // вывод подходящих врачей
                    if (arr[i] == 1) {
                        cout << "Врач " << d.fio << ": " <<
                            specialityName(doctors[i].specialty) << ", " <<
                            qualificationName(doctors[i].qualification) << endl;
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
                cout << "(1-терапевт, 2-кардиолог, 3-стоматолог, 4-любая "
                    "специальность): ";
                SetConsoleTextAttribute(h, 15);

                int speciality_filter;
                // проверка на корректность ввода
                while (!(cin >> speciality_filter) || (speciality_filter > 4) ||
                    (speciality_filter < 1)) {
                    callError(h);

                    SetConsoleTextAttribute(h, 3);
                    cout << "\nВыберите фильтр по специальности врача." << endl;
                    cout << "(1-терапевт, 2-кардиолог, 3-стоматолог, 4-любая "
                        "специальность): ";
                    SetConsoleTextAttribute(h, 15);

                    cin.clear();
                    cin.ignore(132, '\n');
                }

                SetConsoleTextAttribute(h, 3);
                cout << "\nВыберите фильтр по квалификации врача." << endl;
                cout << "(0-высшая, 1-первая, 2-вторая, 3-любая квалификация): ";
                SetConsoleTextAttribute(h, 15);

                int qualification_filter;
                while (!(cin >> qualification_filter) || (qualification_filter > 3) ||
                    (qualification_filter < 0)) {
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
                    if (((doctors[i].specialty == speciality_filter) ||
                        (speciality_filter == 4)) &&
                        ((doctors[i].qualification == qualification_filter) ||
                            (qualification_filter == 3))) {
                        cout << "\nВрач " << doctors[i].fio << ": " <<
                            specialityName(doctors[i].specialty) << ", " <<
                            qualificationName(doctors[i].qualification);
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
                doctor* sorted = sortAlpha(doctors, doctors_counter);
                for (int i = 0; i < doctors_counter; i++) {
                    cout << "\nВрач " << sorted[i].fio << ": " <<
                        specialityName(sorted[i].specialty) << ", " <<
                        qualificationName(sorted[i].qualification);
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
