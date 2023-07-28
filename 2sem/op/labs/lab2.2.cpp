#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;

class Fio {
  char * surname;
  char * name;
  char * patronymic;
  friend class Clinic;

  public:
    Fio(char * p_surname, char * p_name, char * p_patronymic) {
      surname = p_surname;
      name = p_name;
      patronymic = p_patronymic;
    }

  Fio(string p_surname, string p_name, string p_patronymic) {
    char * p_surname2 = new char[p_surname.length() + 1];
    strcpy(p_surname2, p_surname.c_str());
    surname = p_surname2;

    char * p_name2 = new char[p_name.length() + 1];
    strcpy(p_name2, p_name.c_str());
    name = p_name2;

    char * p_patronymic2 = new char[p_patronymic.length() + 1];
    strcpy(p_patronymic2, p_patronymic.c_str());
    patronymic = p_patronymic2;
  }

  Fio() {
    string defaultFio = "default";
    surname = & defaultFio[0];
    name = & defaultFio[0];
    patronymic = & defaultFio[0];
  }

  Fio(const Fio & f) {
    surname = f.surname;
    name = f.name;
    patronymic = f.patronymic;
  }

  char * getSurname() {
    return surname;
  }
  char * getName() {
    return name;
  }
  char * getPatronymic() {
    return patronymic;
  }

};

class Clinic {
  int speciality;
  int qualification;

  friend void findDoctor(Clinic * p_doctors, Fio p_fio, HANDLE h);
  friend void saveData(Clinic * doctors);

  public:
    Fio fio;
  static int count;

  Clinic(Fio p_fio, int p_speciality, int p_qualification) {
    count++;

    fio = p_fio;
    speciality = p_speciality;
    qualification = p_qualification;

  }
  Clinic() {
    fio = Fio();
    speciality = -1;
    qualification = -1;
  }

  bool doctorFilter(int speciality_filter, int qualification_filter) {
    return (((speciality == speciality_filter) || (speciality_filter == 4)) && ((qualification == qualification_filter) || (qualification_filter == 3)));
  }

};

// сортировка врачей по алфавиту
void * sortAlpha(string * fios) {
  string temp;

  for (int i = 0; i < Clinic::count - 1; i++) {
    for (int j = 0; j < Clinic::count - 1; j++) {
      if (fios[j] > fios[j + 1]) {

        temp = fios[j];
        fios[j] = fios[j + 1];
        fios[j + 1] = temp;

      }
    }
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

// поиск врачей по ФИО
void findDoctor(Clinic * p_doctors, Fio p_fio, HANDLE h) {

  int findstatus = 0;

  for (int i = 0; i < Clinic::count; i++) {
    if ((strcmp(p_doctors[i].fio.getSurname(), p_fio.getSurname()) == 0) && (strcmp(p_doctors[i].fio.getName(), p_fio.getName()) == 0) && (strcmp(p_doctors[i].fio.getPatronymic(), p_fio.getPatronymic()) == 0)) {
      cout << "Врач " << p_doctors[i].fio.getSurname() << " " << p_doctors[i].fio.getName() << " " << p_doctors[i].fio.getPatronymic() << ": " << specialityName(p_doctors[i].speciality) << ", " << qualificationName(p_doctors[i].qualification) << endl;
      findstatus = 1;
    }
  }
  if (findstatus == 0) {
    SetConsoleTextAttribute(h, 4);
    cout << "Такого врача нет.\n";
    SetConsoleTextAttribute(h, 15);
  }
}

// добавление нового врача
Clinic * addDoctor(Clinic * p_doctors, Fio fio, int p_specialty, int p_qualification) {

  // копирование всех старых врачей в расширенный массив
  Clinic * newArr = new Clinic[Clinic::count + 1];
  std::copy(p_doctors, p_doctors + min(Clinic::count, Clinic::count + 1), newArr);
  delete[] p_doctors;
  p_doctors = newArr;

  // добавление нового врача
  Clinic newdoctor = Clinic(fio, p_specialty, p_qualification);
  p_doctors[Clinic::count - 1] = newdoctor;
  return p_doctors;

}

// сохранение данных на диске
void saveData(Clinic * doctors) {

  // поток для записи
  ofstream out;
  out.open("hospital_data2.txt");
  if (out.is_open()) {
    // запись количества врачей первой строкой
    out << Clinic::count << endl;
    // запись соответствующих параметров для каждого врача
    for (int i = 0; i < Clinic::count; i++) {
      out << doctors[i].fio.getSurname() << endl;
      out << doctors[i].fio.getName() << endl;
      out << doctors[i].fio.getPatronymic() << endl;
      out << doctors[i].speciality << endl;
      out << doctors[i].qualification << endl;

    }
  }
  out.close();
}

// загрузка данных с диска
Clinic * loadData() {

  ifstream myfile;
  myfile.open("hospital_data2.txt");

  string s;
  int counter;
  int local_speciality;
  int local_qualification;
  char * local_surname;
  char * local_name;
  char * local_patronymic;

  // чтение количества врачей
  getline(myfile, s);
  counter = stoi(s);

  Clinic * l_doctors = new Clinic[Clinic::count + 1];

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

    getline(myfile, s);
    local_speciality = std::stoi(s);

    getline(myfile, s);
    local_qualification = std::stoi(s);

    l_doctors = addDoctor(l_doctors, localfio, local_speciality, local_qualification);

  }

  // закрытие файла
  myfile.close();

  Clinic::count = counter;
  return l_doctors;
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

// вывод списка врачей
void printDoctors(Clinic * doctors) {
  for (int i = 0; i < Clinic::count; i++) {
    cout << "\nВрач №" << i + 1 << ":\n";
    cout << "ФИО врача: " << doctors[i].fio.getSurname() << " " << doctors[i].fio.getName() << " " << doctors[i].fio.getPatronymic() << endl;
  }
}

bool isNonValid(string s) {
  return s.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZaбвгдеёжзыиклмнопрстуфхцчшщьъюяёАБВГДЭЕЖЗЫИКЛМНОПРСТУФХЦЧШЩЬЪЮЯЁ") != std::string::npos;
}

int Clinic::count = 0;

int main() {
  // сохранение исходных параметров кодировки
  int oldin = GetConsoleCP();
  int oldout = GetConsoleOutputCP();

  // установка необходимых параметров кодировки
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  // русификация программы
  setlocale(LC_ALL, "Russian");

  // массив врачей
  Clinic * doctors = new Clinic[Clinic::count + 1];

  // открытие файла в режиме чтения 
  FILE * g;
  g = fopen("hospital_data2.txt", "r");

  // проверка существования файла
  if (g) {
    fseek(g, 0, SEEK_END);
    long pos = ftell(g);

    // проверка файла на пустоту
    if (pos > 2) {
      fclose(g);
      doctors = loadData();
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
      saveData(doctors);
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
        int firstEnter = 0;

        do {
          if (firstEnter != 0) {
            callError(h);
          }
          firstEnter = 1;
          cin >> surname >> name >> patronymic;
        }
        while ((isNonValid(surname) + isNonValid(name) + isNonValid(patronymic)) != 0);

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

        // формирование ФИО нового врача
        string p_fio = (surname + " " + name + " " + patronymic);
        char * p_fio2 = new char[p_fio.length() + 1];
        strcpy(p_fio2, p_fio.c_str());

        Fio localfio = Fio(surname, name, patronymic);
        // создание указателя на нового врача
        doctors = addDoctor(doctors, localfio, p_speciality, p_quality);

        current_status = 0;
      }
      break;

      // печать информации о врачах
    case 2:
      current_status = 1;
      while (current_status) {

        printDoctors(doctors);

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

        Fio findFio = Fio(surname, name, patronymic);

        findDoctor(doctors, findFio, h);

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
        for (int i = 0; i < Clinic::count; i++) {

          // вывод подходящих врачей
          if (doctors[i].doctorFilter(speciality_filter, qualification_filter)) {
            cout << "\nВрач " << doctors[i].fio.getSurname() << " " << doctors[i].fio.getName() << " " << doctors[i].fio.getPatronymic();
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

        string * fios = new string[Clinic::count];

        for (int i = 0; i < Clinic::count; i++) {

          string surname = doctors[i].fio.getSurname();
          string name = doctors[i].fio.getName();
          string patronymic = doctors[i].fio.getPatronymic();

          fios[i] = (surname + " " + name + " " + patronymic);
        }

        sortAlpha(fios);

        for (int i = 0; i < Clinic::count; i++) {
          cout << "\nВрач " << fios[i];

        }

        delete[] fios;

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

  delete[] doctors;

  // установка исходных параметров кодировки
  SetConsoleCP(oldin);
  SetConsoleOutputCP(oldout);

  system("pause");
  return 0;

}