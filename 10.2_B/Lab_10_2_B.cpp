// Lab_10_2_B.cpp
// Данилевич Данило
// Лабораторна робота № 10.2 (Рівень В)
// Впорядкування та бінарний пошук в масиві структур з об'єднаннями
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
    union
    {
        int programuvannia;
        int chyselni_metody;
        int pedahohika;
    };
};

int Utf8Length(const string& s)
{
    int len = 0;
    for (char ch : s)
        if ((static_cast<unsigned char>(ch) & 0xC0) != 0x80)
            len++;
    return len;
}

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

int GetThirdMark(const Student& s)
{
    switch (s.spec)
    {
    case KN:  return s.programuvannia;
    case INF: return s.chyselni_metody;
    default:  return s.pedahohika;
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

        switch (p[i].spec)
        {
        case KN:
            p[i].programuvannia = InputInt("    оцінка з програмування (1 - 5): ", 1, 5);
            break;
        case INF:
            p[i].chyselni_metody = InputInt("    оцінка з чисельних методів (1 - 5): ", 1, 5);
            break;
        default:
            p[i].pedahohika = InputInt("    оцінка з педагогіки (1 - 5): ", 1, 5);
            break;
        }
        cout << endl;
    }
}

void PrintRow(const Student& s, int index)
{
    cout << "| " << setw(3) << right << index << " ";
    cout << "| " << PadLeft(s.prizv, 13);
    cout << "|  " << setw(2) << right << s.kurs << "  ";
    cout << "| " << PadLeft(specStr[s.spec], 24);
    cout << "|   " << setw(2) << right << s.fizyka << "   ";
    cout << "|     " << setw(2) << right << s.matematyka << "     ";

    switch (s.spec)
    {
    case KN:
        cout << "|      " << setw(2) << right << s.programuvannia << "       |                 |            |" << endl;
        break;
    case INF:
        cout << "|               |       " << setw(2) << right << s.chyselni_metody << "        |            |" << endl;
        break;
    default:
        cout << "|               |                 |     " << setw(2) << right << s.pedahohika << "     |" << endl;
        break;
    }
}

void Print(const Student* p, const int N)
{
    cout << "=============================================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |      Спеціальність      | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
        PrintRow(p[i], i + 1);

    cout << "=============================================================================================================================" << endl;
    cout << endl;
}

bool IsGreater(const Student& a, const Student& b)
{
    if (specStr[a.spec] != specStr[b.spec])
        return specStr[a.spec] > specStr[b.spec];
    int mA = GetThirdMark(a);
    int mB = GetThirdMark(b);
    if (mA != mB)
        return mA > mB;
    return a.prizv > b.prizv;
}

void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (IsGreater(p[i1], p[i1 + 1]))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* IndexSort(const Student* p, const int N)
{
    int* I = new int[static_cast<size_t>(N)];
    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1; j >= 0 && IsGreater(p[I[j]], p[value]); j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(const Student* p, const int* I, const int N)
{
    cout << "=============================================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |      Спеціальність      | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
        PrintRow(p[I[i]], i + 1);

    cout << "=============================================================================================================================" << endl;
    cout << endl;
}

int BinSearch(const Student* p, const int N, const string prizv, const Specialnist spec, const int thirdMark)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        int mThird = GetThirdMark(p[m]);
        if (p[m].spec == spec && mThird == thirdMark && p[m].prizv == prizv)
            return m;
        if ((specStr[p[m].spec] < specStr[spec]) ||
            (specStr[p[m].spec] == specStr[spec] && mThird < thirdMark) ||
            (specStr[p[m].spec] == specStr[spec] && mThird == thirdMark && p[m].prizv < prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

#ifndef UNIT_TEST
int main()
{
    int N = InputInt("Введіть кількість студентів N: ", 1, 100);
    Student* p = new Student[static_cast<size_t>(N)];

    bool isCreated = false;
    int menuItem;
    do {
        cout << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << "  [1] - введення даних з клавіатури" << endl;
        cout << "  [2] - вивід даних на екран" << endl;
        cout << "  [3] - фізичне впорядкування даних" << endl;
        cout << "  [4] - індексне впорядкування та вивід даних" << endl;
        cout << "  [5] - бінарний пошук студента за спеціальністю, оцінкою з третього предмету та прізвищем" << endl;
        cout << "  [0] - вихід та завершення роботи програми" << endl << endl;
        menuItem = InputInt("Введіть значення: ", 0, 5);
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
            {
                Sort(p, N);
                cout << "Масив фізично впорядковано!" << endl;
            }
            break;
        case 4:
            if (!isCreated)
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            else
            {
                int* I = IndexSort(p, N);
                PrintIndexSorted(p, I, N);
                delete[] I;
            }
            break;
        case 5:
            if (!isCreated)
                cout << "Спочатку введіть дані (пункт [1])!" << endl;
            else
            {
                cout << "Введіть ключі пошуку:" << endl;
                int ispec = InputInt("    спеціальність (0 - КН, 1 - Інф, 2 - МЕ, 3 - ФІ, 4 - ТН): ", 0, 4);
                Specialnist spec = (Specialnist)ispec;
                int mark = InputInt("    оцінка з третього предмету (1 - 5): ", 1, 5);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string prizv;
                cout << "    прізвище: ";
                getline(cin, prizv);
                cout << endl;

                int found = BinSearch(p, N, prizv, spec, mark);
                if (found != -1)
                    cout << "Знайдено студента в позиції " << found + 1 << endl;
                else
                    cout << "Шуканого студента не знайдено" << endl;
            }
            break;
        case 0:
            break;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}
#endif
