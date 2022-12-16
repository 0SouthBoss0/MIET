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
#include <windows.h>

using namespace std;

// ������������ ���������� ������, �������������� ������
#define DEPOSITS_MAX 50

// ������������ �������� ������
#define BUFFER_LENGTH 80

// ��������� ����������� �����
struct deposit {
    int number; // ����� �����
    char* surname; // ������� ������� 
    char* name; // ��� �������
    double balance; // ����� �� �����
};

// ����� ���������� � ���������� �����
void printAccount(struct deposit* account) {

    cout << "\n���������� � ����� �" << account->number << ":\n";
    cout << "������� �������: " << account->surname << endl;
    cout << "��� �������: " << account->name << endl;
    cout << "������ �����: " << account->balance << "$" << endl << endl;

}

// �������� ������ ����������� �����
void openAccount(struct deposit* account, int number, double balance) {

    // ��������� ���������� ����������� ����� �������������� ���������� �������
    account->balance = balance;
    account->number = number;
}

// �������� ������� ������� ����� � ������� �������� � ������
void findClients(struct deposit* account, int* arr, char* surname, char* name, int i) {

    // �������� ���������� ������ � ���������������� ����������� ����������� ����� 
    if (strcmp(surname, account->surname) == 0 && strcmp(name, account->name) == 0) {
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

    cout << "������� ���������. ������ ������ �����. �������� ����������� �������.\n\n";

    // �������� ���� ������ ���������
    while (status) {
        SetConsoleTextAttribute(h, 2);
        cout << "�������� ����� ����: ...................................1" << endl;
        cout << "����������� ���������� � �����: ........................2" << endl;
        cout << "���������� ��� ����� � ������, ������ ��������: ........3" << endl;
        cout << "����� ��� ����� ��������� ������� (��� + �������): .....4" << endl;
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
                deposits[deposits_counter].surname = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].surname, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "������� ���: ";
                SetConsoleTextAttribute(h, 15);

                // ���������� ������, �������� �������������
                cin >> buff;

                // ��������� ����� ������� ��� ������ ����������� �����
                deposits[deposits_counter].name = new char[strlen(buff) + 1];
                strcpy(deposits[deposits_counter].name, buff);

                SetConsoleTextAttribute(h, 3);
                cout << "������� ������: (���������� ����������� - �����): ";
                SetConsoleTextAttribute(h, 15);

                // ���������� �������, ��������� �������������
                double balance_input;
                cin >> balance_input;

                // �������� ��������� �� ����� ���������� ����
                struct deposit* p_deposit = &deposits[deposits_counter];

                // ��������� ������ � ������� ��� ������ ����������� �����
                openAccount(p_deposit, deposits_counter + 1, balance_input);
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
                int sum_to_look;
                cin >> sum_to_look;

                // ���������� ��� ������ ����� ������� - ���� ���������� ������ ���, �� ����� �� �����
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    //��������� ������� �������� ����������� ����� � ������, ��������� �������������
                    if (deposits[i].balance > sum_to_look) {
                        if (flag == 0) {
                            cout << "\n(����� �����, �������, ���, ������ �����)\n";
                        }
                        cout << "�" << i + 1 << " - " << deposits[i].surname << " " << deposits[i].name << ", " << deposits[i].balance << "$" << "\n";
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

                // ������ �������� ���������� ������ � �������� �������� � ������ �������
                int* arr = new int[deposits_counter];

                // ���������� ������� �������� ���������� ������
                for (int i = 0; i < deposits_counter; i++) {

                    // �������� ��������� �� ������� ���������� ����
                    struct deposit* p_deposit = &deposits[i];

                    // ��������� ������� ������� � ����� ������� � ��������������� �������� ����������� �����
                    findClients(p_deposit, arr, surname_to_find, name_to_find, i);
                }

                // ���������� ��� ������ ����� ������� - ���� ���������� ������ ���, �� ����� �� �����
                int flag = 0;

                for (int i = 0; i < deposits_counter; i++) {

                    // ����� ���������� ���������� ������
                    if (arr[i] == 1) {
                        if (flag == 0) {
                            cout << "\n����� ������� " << surname_to_find << " " << name_to_find << " (�����, ������):\n";
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

            // �������� �� ������������ ����� ������ ������
        default:
            SetConsoleTextAttribute(h, 4);
            printf("\n��������� ������������ �������� ������.\n\n");
            SetConsoleTextAttribute(h, 15);
        }
    }

    // ��������� �������� ���������� ���������
    SetConsoleCP(oldin);
    SetConsoleOutputCP(oldout);

    system("pause");
    return 0;

}
/*
Created by SouthBoss at 2022
*/