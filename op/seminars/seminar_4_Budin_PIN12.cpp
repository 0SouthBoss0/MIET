#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
using namespace std;

struct student {
	char** name;
	int group;
	int ses[5];
};

void head()
{
	cout << "\n\n";
	cout << "ФИО студента" << "\tНомер группы" << "\tУспеваемость\n";
	for (int i = 0; i < 120; i++)
	{
		cout << "-";
	}
	cout << "\n";
}

void add_new_student(struct student arr[], int& k) {

	cout << "ФИО студента: ";
	arr[k].name = (char**)malloc(2 * sizeof(char*));
	char buff1[80] = {};
	char buff2[80] = {};
	cin >> buff1;
	cin >> buff2;
	arr[k].name[0] = (char*)malloc((strlen(buff1) + 1) * sizeof(char));
	arr[k].name[1] = (char*)malloc((strlen(buff2) + 1) * sizeof(char));
	strcpy(arr[k].name[0], buff1);
	strcpy(arr[k].name[1], buff2);

	cout << "Номер группы: ";
	cin >> arr[k].group;

	cout << "Успеваемость(оценки): ";
	cin >> arr[k].ses[0] >> arr[k].ses[1] >> arr[k].ses[2] >> arr[k].ses[3] >> arr[k].ses[4];

	k++;
}

void print_student(struct student arr[], int k) {
	head();
	for (int i = 0; i < k * 2; i += 2) {
		cout << arr[i].name[0] << " " << arr[i].name[1] << "\t" << arr[i].group << "\t\t" << arr[i].ses[0] << " " << arr[i].ses[1] << " " << arr[i].ses[2] << " " << arr[i].ses[3] << " " << arr[i].ses[4] << "\n";
	}
	for (int i = 0; i < 120; i++) {
		cout << "-";
	}
	cout << "\n\n";
}

void print_bad_student(struct student arr[], int k) {
	bool flag = 1;
	for (int i = 0; i < k * 2; i += 2) {
		if ((arr[i].ses[0] == 2) || (arr[i].ses[1] == 2) || (arr[i].ses[2] == 2) || (arr[i].ses[3] == 2) || (arr[i].ses[4] == 2)) {
			cout << arr[i].name[0] << " " << arr[i].name[1] << "\t\t" << arr[i].group << "\n";
			flag = 0;
		}
	}
	if (flag == 1) {
		cout << "Двоечников нет\n";
	}

	cout << "\n\n";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	struct student* Arr;
	Arr = (struct student*)malloc(sizeof(Arr) * 10);
	char y = 'y';
	int f;
	int k = 0;
	while (true) {
		cout << "Доступные функции:" << endl;
		cout << "1.Добавить нового студента\n" << "2.Распечатать информацию о студентах\n" << "3.Найти всех студентов с оценкой '2' \n\n";
		cout << "Выберите функцию: ";
		cin >> f;
		switch (f) {
		case 1:
			add_new_student(Arr + k, k);
			break;
		case 2:
			print_student(Arr, k);
			break;
		case 3:
			print_bad_student(Arr, k);
			break;
		}
		cout << endl;
	}
	free(Arr);
	return 0;
}