// Lab_10_1_A.cpp
// Данилевич Данило
// Лабораторна робота № 10.1 (Рівень А)
// Послідовний пошук в масиві структур
// Варіант 7

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

enum Specialnist { KN, INF, ME, FI, TN };

string specStr[] = {
    "Комп'ютерні науки",
    "Інформатика",
    "Математика та економіка",
    "Фізика та інформатика",
    "Трудове навчання"
};

struct Student
{
    string      prizv;
    unsigned    kurs;
    Specialnist spec;
    int         fizyka;
    int         matematyka;
    int         informatyka;
};

// Допоміжна функція для підрахунку кількості символів у UTF-8 рядку
int Utf8Length(const string& s)
{
    int len = 0;
    for (char ch : s)
        if ((static_cast<unsigned char>(ch) & 0xC0) != 0x80)
            len++;
    return len;
}

// Допоміжна функція для вирівнювання UTF-8 тексту по лівому краю
string PadLeft(const string& s, int width)
{
    int len = Utf8Length(s);
    if (len >= width)
        return s;
    return s + string(static_cast<size_t>(width - len), ' ');
}

int InputInt(const string& prompt, int minVal, int maxVal)
{
    int val;
    while (true)
    {
        cout << prompt;
        if (cin >> val && val >= minVal && val <= maxVal)
            return val;
        cout << "Помилка! Введіть ціле число від " << minVal << " до " << maxVal << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Create(Student* p, const int N)
{
    int spec;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "    прізвище: ";
        getline(cin, p[i].prizv);
        p[i].kurs = (unsigned)InputInt("    курс (1 - 6): ", 1, 6);
        spec = InputInt("    спеціальність (0 - КН, 1 - Інф, 2 - МЕ, 3 - ФІ, 4 - ТН): ", 0, 4);
        p[i].spec = (Specialnist)spec;
        p[i].fizyka = InputInt("    оцінка з фізики (1 - 5): ", 1, 5);
        p[i].matematyka = InputInt("    оцінка з математики (1 - 5): ", 1, 5);
        p[i].informatyka = InputInt("    оцінка з інформатики (1 - 5): ", 1, 5);
        cout << endl;
    }
}

void Print(const Student* p, const int N)
{
    cout << "===============================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |      Спеціальність      | Фізика | Математика | Інформатика |" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << PadLeft(p[i].prizv, 13);
        cout << "|  " << setw(2) << right << p[i].kurs << "  ";
        cout << "| " << PadLeft(specStr[p[i].spec], 24);
        cout << "|   " << setw(2) << right << p[i].fizyka << "   ";
        cout << "|     " << setw(2) << right << p[i].matematyka << "     ";
        cout << "|     " << setw(2) << right << p[i].informatyka << "      |" << endl;
    }

    cout << "===============================================================================================" << endl;
    cout << endl;
}

double CalcAverage(const Student& s)
{
    return (s.fizyka + s.matematyka + s.informatyka) / 3.0;
}

void PrintAverages(const Student* p, const int N)
{
    cout << "Середній бал кожного студента:" << endl;
    cout << "-------------------------------------" << endl;
    cout << "|  №  |   Прізвище   | Середній бал |" << endl;
    cout << "-------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " "
             << "| " << PadLeft(p[i].prizv, 13)
             << "|     " << setw(5) << fixed << setprecision(2) << right << CalcAverage(p[i]) << "    |" << endl;
    }
    cout << "-------------------------------------" << endl;
    cout << endl;
}

double PercentPhysics45(const Student* p, const int N)
{
    if (N <= 0)
        return 0.0;
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        if (p[i].fizyka == 5 || p[i].fizyka == 4)
            k++;
    }
    return 100.0 * k / N;
}

#ifndef UNIT_TEST
int main()
{
    int N = InputInt("Введіть кількість студентів N: ", 1, 100);
    Student* p = new Student[N];

    bool isCreated = false;
    int menuItem;
    do {
        cout << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << "  [1] - введення даних з клавіатури" << endl;
        cout << "  [2] - вивід даних на екран" << endl;
        cout << "  [3] - вивід прізвищ та середнього балу кожного студента" << endl;
        cout << "  [4] - обчислення проценту студентів, які отримали з фізики оцінки 5 або 4" << endl;
        cout << "  [0] - вихід та завершення роботи програми" << endl << endl;
        menuItem = InputInt("Введіть значення: ", 0, 4);
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Create(p, N);
            isCreated = true;
            break;
        case 2:
            if (!isCreated)
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            else
                Print(p, N);
            break;
        case 3:
            if (!isCreated)
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            else
                PrintAverages(p, N);
            break;
        case 4:
            if (!isCreated)
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            else
                cout << "Процент студентів, які отримали з фізики оцінки \"5\" або \"4\": "
                     << fixed << setprecision(2) << PercentPhysics45(p, N) << "%" << endl;
            break;
        case 0:
            break;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}
#endif
