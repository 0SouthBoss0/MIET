/*
Created by SouthBoss at 2022
*/

/*
� ������ ���� ����������� ������������ ������:

��������� ����� ���������� ����������
�������� ����, ������� �� ������ �������� ����.
��������� / ������
� ������� ���������� Lucida Console
��������� ������ ������.
*/

#include <iostream>
#include <string>
#include <locale>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <string.h>

using namespace std;

// ������������ ���������� ������, �������������� ������
#define DEPOSITS_MAX 50

// ������������ �������� ������
#define BUFFER_LENGTH 80

// ��������� ���
typedef struct fio {
    char* surname; // ������� 
    char* name; // ��� 
    char* patronymic; // ��������
};

// ��������� ����
typedef struct date {
    int day; // ���� 
    int month; // ����� 
    int year; // ���
};

// ��������� ����������� �����
struct deposit {
    fio client; // ��� �������
    date creation_date; // ���� �������� �����
    int number; // ����� �����
    double balance; // ����� �� �����
};

// �������� ������ � �����
void loadData(struct deposit* deposits, int* global_counter) {
    int counter;
    int number;
    double d_number;
    string s;

    // ���� �� �����
    ifstream file("bank_data.txt");

    // ���������� �������� ������
    getline(file, s);
    counter = std::stoi(s);
    (*global_counter) = counter;

    // ���� �� ���� ������ �� �����
    for (int i = 0; i < counter; i++) {

        // ����� �����
        getline(file, s);
        number = std::stoi(s);
        deposits[i].number = number;

        // ������� �������
        getline(file, s);
        deposits[i].client.surname = new char[strlen(s.c_str()) + 1];
        strcpy(deposits[i].client.surname, s.c_str());

        // ��� �������
        getline(file, s);
        deposits[i].client.name = new char[strlen(s.c_str()) + 1];
        strcpy(deposits[i].client.name, s.c_str());

        // �������� �������
        getline(file, s);
        deposits[i].client.patronymic = new char[strlen(s.c_str()) + 1];
        strcpy(deposits[i].client.patronymic, s.c_str());

        // ���� �������� �����
        getline(file, s);
        number = std::stoi(s);
        deposits[i].creation_date.day = number;

        // ����� �������� �����
        getline(file, s);
        number = std::stoi(s);
        deposits[i].creation_date.month = number;

        // ��� �������� �����
        getline(file, s);
        number = std::stoi(s);
        deposits[i].creation_date.year = number;

        // ������ �����
        getline(file, s);
        d_number = std::stod(s);
        deposits[i].balance = d_number;

    }

    // �������� �����
    file.close();
}

// ���������� ������ �� ����
void saveData(struct deposit* deposits, int deposits_counter) {

    // �������� ����� � ������ ���������
    FILE* file;
    file = fopen("bank_data.txt", "w");

    // ������ ���������� �������� ������ ������ ������� �����
    fprintf(file, "%d\n", deposits_counter);

    // ���� �� ���� �������� ������ - ���������� ������ ������ � ����
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

    // �������� �����
    fclose(file);
}

// ����� ���������� � ���������� �����
void printAccount(struct deposit* account) {
    cout << "\n���������� � ����� �" << account->number << ":\n";
    cout << "������� �������: " << account->client.surname << endl;
    cout << "��� �������: " << account->client.name << endl;
    cout << "�������� �������: " << account->client.patronymic << endl;
    cout << "���� �������� �����: " << account->creation_date.day << "." << account->creation_date.month << "." << account->creation_date.year << endl;
    cout << "������ �����: " << account->balance << "$" << endl << endl;
}

// �������� ������������� ���� �������� ����� ��� �����
bool isBigger(int day_to_find, int month_to_find, int year_to_find, int day, int month, int year) {

    // �������� ��� ����������� ��� �������� �����
    if (year_to_find > year) {
        return false;
    }

    // �������� ��� ����� ���� �������� �����
    if (year_to_find == year) {
        // �������� ����� ����������� ����� �������� �����
        if (month_to_find > month) {
            return false;
        }
    }

    // �������� ��� ����� ���� �������� �����
    if (year_to_find == year) {
        // �������� ����� ����� ������ �������� �����
        if (month_to_find == month) {
            // �������� ���� ����������� ���� �������� �����
            if (day_to_find >= day) {
                return false;
            }
        }
    }

    // ���� �������� ����� ����������� ��� �����
    return true;
}

// �������� ������ ����������� �����
void openAccount(struct deposit* account, int number, double balance, int day, int month, int year) {

    // ��������� ���������� ����������� ����� �������������� ���������� �������
    account->balance = balance;
    account->number = number;
    account->creation_date.day = day;
    account->creation_date.month = month;
    account->creation_date.year = year;
}

// �������� ������� ������� ����� � ������� �������� � ������
void findClients(struct deposit* account, int* arr, char* surname, char* name, char* patronymic, int i) {

    // �������� ���������� ������ � ���������������� ����������� ����������� ����� 
    if (strcmp(surname, account->client.surname) == 0 && strcmp(name, account->client.name) == 0 && strcmp(patronymic, account->client.patronymic) == 0) {
        *(arr + i) = 1;
    }
    else {
        *(arr + i) = 0;
    }
}

int main() {

    // ���������� �������� ���������� ���������
    int oldin = GetConsoleCP();
    int oldout = GetConsoleOutputCP();

    // ��������� ����������� ���������� ���������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ����������� ���������
    setlocale(LC_ALL, "Russian");

    // ��������� ����������� ���� ��� ��������� ����� ������
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);

    // ����������, ���������� �� ��������� � ����� �� ������
    int status = 1;
    int current_status = 0;

    // ������� �������� ���������� �������� ���������� ������
    int deposits_counter = 0;

    // ������ ���������� ������
    struct deposit deposits[DEPOSITS_MAX];

    // �������� ����� � ������ ������ 
    FILE* g;
    g = fopen("bank_data.txt", "r");

    // �������� ������������� �����
    if (g) {
        fseek(g, 0, SEEK_END);
        long pos = ftell(g);

        // �������� ����� �� �������
        if (pos > 2) {
            loadData(deposits, &deposits_counter);
        }
    }

    cout << "������� ���������. ������ ������ �����. �������� ����������� �������.\n\n";

    // �������� ���� ������ ���������
    while (status) {
        SetConsoleTextAttribute(h, 2);
        cout << "�������� ����� ����: ...................................1" << endl;
        cout << "����������� ���������� � �����: ........................2" << endl;
        cout << "���������� ��� ����� � ������, ������ ��������: ........3" << endl;
        cout << "����� ��� ����� ��������� �������: .....................4" << endl;
        cout << "����� ��� �����, �������� ����� �������� ����: .........5" << endl;
        cout << "���������� ������: .....................................0" << endl;
        SetConsoleTextAttribute(h, 15);

        // ���������� �������, ��������� �������������
        int task_chosen;
        cin >> task_chosen;

        // ������� � ������, ��������� �������������
        switch (task_chosen) {

            // ���������� ���������
        case 0:
            status = 0;
            printf("\n��������� ���������.\n");
            break;

            // ���������� ������ �����
        case 1:
            current_status = 1;
            while (current_status) {

                // �������� ������ 
                char buff[BUFFER_LENGTH];

                SetConsoleTextAttribute(h, 3);
                cout << "������� �������: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� ������, �������� �������������
                cin >> buff;

                // ��������� ������� ������� ��� ������ ����������� �����
                deposits[deposits_counter].client.surname = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].client.surname, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "������� ���: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� ������, �������� �������������
                cin >> buff;

                // ��������� ����� ������� ��� ������ ����������� �����
                deposits[deposits_counter].client.name = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].client.name, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "������� ��������: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� ������, �������� �������������
                cin >> buff;

                // ��������� ������� ������� ��� ������ ����������� �����
                deposits[deposits_counter].client.patronymic = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].client.patronymic, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "������� ������: (���������� ����������� - �����): ";
                SetConsoleTextAttribute(h, 15);

                // ���������� �������, ��������� �������������
                double balance_input;
                cin >> balance_input;

                struct date current_date;
                time_t now = time(0);
                tm* ltm = localtime(&now);

                current_date.day = ltm->tm_mday;
                current_date.month = 1 + ltm->tm_mon;
                current_date.year = 1900 + ltm->tm_year;

                // �������� ��������� �� ����� ���������� ����
                struct deposit* p_deposit = &deposits[deposits_counter];

                // ��������� ������ � ������� ��� ������ ����������� �����
                openAccount(p_deposit, deposits_counter + 1, balance_input, current_date.day, current_date.month, current_date.year);
                cout << "\n����� ��������� �����: " << deposits_counter + 1 << "\n" << endl;

                // ��������� �������� ���������� �������� ���������� ������
                deposits_counter += 1;
                current_status = 0;
            }
            break;

            // ������ ���������� � �����
        case 2:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\n������� ����� �����: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� ������ ����������� �����, ��������� �������������
                int deposit_index;
                cin >> deposit_index;

                // �������� ���������� ������ ����������� �����, ��������� �������������
                if (deposit_index > deposits_counter || deposit_index <= 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\n������ ����� �� ����������. ��������� �����.\n\n";
                    SetConsoleTextAttribute(h, 15);
                    break;
                }

                // �������� ��������� �� ������� ���������� ����
                struct deposit* p_deposit = &deposits[deposit_index - 1];

                // ����� ���������� � ������� ���������� �����
                printAccount(p_deposit);

                current_status = 0;
            }
            break;

            // ����������� ���� ������ � ��������, ������ �������� ������������� �����
        case 3:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\n������� ����� ��� ������ ������, ������ ������� ������ ���������: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� �����, �������� �������������
                double sum_to_look;
                cin >> sum_to_look;

                // ���������� ��� ������ ����� ������� - ���� ���������� ������ ���, �� ����� �� �����
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    //��������� ������� �������� ����������� ����� � ������, ��������� �������������
                    if (deposits[i].balance > sum_to_look) {
                        if (flag == 0) {
                            cout << "\n(����� �����, �������, ���, ��������, ������ �����)\n";
                        }
                        cout << "�" << i + 1 << " - " << deposits[i].client.surname << " " << deposits[i].client.name << " " << deposits[i].client.patronymic << ", " << deposits[i].balance << "$" << "\n";
                        flag = 1;
                    }
                }

                // ���� ���������� ������ ���
                if (flag == 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\n����� ������ ���.\n";
                    SetConsoleTextAttribute(h, 15);
                }

                current_status = 0;
            }
            break;

            // ����� ���� ���������� ������ ��������� ������������� �������
        case 4:
            current_status = 1;
            while (current_status) {

                // �������� ������
                char buff[BUFFER_LENGTH];

                SetConsoleTextAttribute(h, 3);
                cout << "������� ������� �������� �������: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� ������, �������� �������������
                cin >> buff;

                // ���������� ������� ������� ��� ������ ���������� ������
                char* surname_to_find;
                surname_to_find = new char[strlen(buff) + 1];
                strcpy(surname_to_find, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "������� ��� �������� �������: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� ������, �������� �������������
                cin >> buff;

                // ���������� ����� ������� ��� ������ ���������� ������
                char* name_to_find;
                name_to_find = new char[strlen(buff) + 1];
                strcpy(name_to_find, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "������� �������� �������� �������: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� ������, �������� �������������
                cin >> buff;

                // ���������� ����� ������� ��� ������ ���������� ������
                char* patronymic_to_find;
                patronymic_to_find = new char[strlen(buff) + 1];
                strcpy(patronymic_to_find, buff);

                // ������ �������� ���������� ������ � �������� �������� � ������ �������
                int* arr = new int[deposits_counter];

                // ���������� ������� �������� ���������� ������
                for (int i = 0; i < deposits_counter; i++) {

                    // �������� ��������� �� ������� ���������� ����
                    struct deposit* p_deposit = &deposits[i];

                    // ��������� ������� ������� � ����� ������� � ��������������� �������� ����������� �����
                    findClients(p_deposit, arr, surname_to_find, name_to_find, patronymic_to_find, i);
                }

                // ���������� ��� ������ ����� ������� - ���� ���������� ������ ���, �� ����� �� �����
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    // ����� ���������� ���������� ������
                    if (arr[i] == 1) {
                        if (flag == 0) {
                            cout << "\n����� ������� " << surname_to_find << " " << name_to_find << " " << patronymic_to_find << " (�����, ������):\n";
                        }
                        cout << "�" << i + 1 << " - " << deposits[i].balance << "$" << "\n";

                        flag = 1;
                    }
                }

                // ���� ���������� ������ ���
                if (flag == 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\n������ ������� ���.\n\n";
                    SetConsoleTextAttribute(h, 15);
                }

                // ������� ������������ ������
                delete[] arr;

                current_status = 0;
            }
            break;
            // ������ ���������� � �����
            // ����������� ���� ������, �������� ����� �������� ������������� ����
        case 5:
            current_status = 1;
            while (current_status) {

                SetConsoleTextAttribute(h, 3);
                cout << "\n������� ���� (DD.MM.YYYY) ��� ������ ������, �������� ����� ��������: ";
                SetConsoleTextAttribute(h, 15);

                // �������� ������ 
                char buff[BUFFER_LENGTH];
                // ���������� ����, �������� �������������
                cin >> buff;

                // ���������� ����, �������� �������������
                char* date_to_find;
                date_to_find = new char[strlen(buff) + 1];
                strcpy(date_to_find, buff);

                // ����������� ������ ����
                char sep[10] = ".";

                // ����������, � ������� ����� ���������� ��������� ������ ������ ������
                char* istr;

                int day_to_find;
                int month_to_find;
                int year_to_find;

                // ��������� ������ ����� ������ (����)
                istr = strtok(date_to_find, sep);
                day_to_find = atoi(istr);

                // ��������� ��������� ����� ������ (�����)
                istr = strtok(NULL, sep);
                month_to_find = atoi(istr);

                // ��������� ��������� ����� ������ (���)
                istr = strtok(NULL, sep);
                year_to_find = atoi(istr);

                // ���������� ��� ������ ����� ������� - ���� ���������� ������ ���, �� ����� �� �����
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    //��������� ���� �������� �������� ����������� ����� � �����, ��������� �������������
                    if (isBigger(day_to_find, month_to_find, year_to_find, deposits[i].creation_date.day, deposits[i].creation_date.month, deposits[i].creation_date.year)) {
                        if (flag == 0) {
                            cout << "\n(����� �����, �������, ���, ��������, ���� ��������, ������ �����)\n";
                        }
                        cout << "�" << i + 1 << " - " << deposits[i].client.surname << " " << deposits[i].client.name << " " << deposits[i].client.patronymic << ", " << deposits[i].creation_date.day << "." << deposits[i].creation_date.month << "." << deposits[i].creation_date.year << ", " << deposits[i].balance << "$" << "\n";
                        flag = 1;
                    }
                }

                // ���� ���������� ������ ���
                if (flag == 0) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "\n����� ������ ���.\n\n";
                    SetConsoleTextAttribute(h, 15);
                }
                current_status = 0;
            }
            break;

            // �������� �� ������������ ����� ������ ������
        default:
            SetConsoleTextAttribute(h, 4);
            printf("\n��������� ������������ �������� ������.\n\n");
            SetConsoleTextAttribute(h, 15);
        }
    }

    // ���������� ������ �� �������� ������
    saveData(deposits, deposits_counter);

    // ��������� �������� ���������� ���������
    SetConsoleCP(oldin);
    SetConsoleOutputCP(oldout);

    system("pause");
    return 0;
}
/*
Created by SouthBoss at 2022
*/