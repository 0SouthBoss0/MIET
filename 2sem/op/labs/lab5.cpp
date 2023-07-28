#include <iostream>
#include <string>
#include <time.h>

using namespace std;

const int ABS_MAX_GENERATE = 50;
const int DIGITS_AFTER_POINT = 2;

// шаблон функции для вывода массива
template <typename T>
void printArray(T* array, int size) {
    printf("\nМассив:\n");
    for (int i = 0; i < size; i++) {
        cout << array[i] << "\t";
    }
    printf("\n");
}

// шаблон функции для поиска индекса максимального элемента в массиве
template <typename T>
int findMax(T* array, int size) {
    int index_max = 0;
    T current_max = array[index_max];

    for (int i = 0; i < size; i++) {
        if (array[i] > current_max) {
            index_max = i;
            current_max = array[index_max];
        }
    }
    return index_max;
}

// шаблон функции для вывода элементов массива после максимального
template <typename T>
void printTask(T* array, int size) {
    cout << ("\nВсе элементы после максимального:\n");
    for (int i = findMax(array, size) + 1; i < size; i++) {
        cout << array[i] << "\t";
    }
    cout << endl;
}

// перегрузка функции для типа double
void printTask(double* array, int size) {
    cout << ("\nВсе элементы до максимального:\n");
    for (int i = 0; i < findMax(array, size); i++) {
        cout << array[i] << "\t";
    }
    cout << endl;
}

// инициализация int массива
void initIntArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = (rand() % ABS_MAX_GENERATE) * pow(-1.0, rand());
    }
}

// инициализация double массива
void initDoubleArray(double* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = int((-ABS_MAX_GENERATE + (double)rand() / RAND_MAX * (2 * ABS_MAX_GENERATE)) * pow(10, DIGITS_AFTER_POINT)) / pow(10, DIGITS_AFTER_POINT);
    }
}

// создание int массива
int* createIntArray(int size) {
    int* arr = new int[size];
    initIntArray(arr, size);
    return arr;
}

// создание double массива
double* createDoubleArray(int size) {
    double* arr = new double[size];
    initDoubleArray(arr, size);
    return arr;
}

// проверка на число
bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) {
        return !std::isdigit(c);
        }) == s.end();
}

int main() {
    // русификация программы
    setlocale(LC_ALL, "Russian");

    // привязка rand() к текущему времени
    time_t k;
    srand(time(&k));

    cout << "Введите размер массивов:...";
    string curr_input;
    int size;

    while (true) {
        cin >> curr_input;
        if (is_number(curr_input)) {
            size = stoi(curr_input);
            break;
        }
        else {
            cout << "\nПроверьте корректность ввода...\n";
        }
    }

    int* int_arr = createIntArray(size);
    printArray(int_arr, size);
    printTask(int_arr, size);

    double* double_arr = createDoubleArray(size);
    printArray(double_arr, size);
    printTask(double_arr, size);

    // очистка динамической памяти
    delete[] int_arr;
    delete[] double_arr;

    system("pause");
    return 0;
}