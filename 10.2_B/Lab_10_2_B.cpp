// Lab_10_2_B.cpp
// Данилевич Данило
// Лабораторна робота № 10.2 (Рівень В)
// Варіант 7

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum Specialnist { KN, INF, ME, FI, TN };
string specStr[] = {
    "Комп'ютерні науки",
    "Інформатика",
    "Математика та економіка",
    "Фізика та інформатика",
    "Трудове навчання"
};

struct Student {
    string prizv;
    unsigned kurs;
    Specialnist spec;
    int fizyka;
    int matematyka;
    union {
        int programuvannya;
        int chyselni_metody;
        int pedagogika;
    };
};

void Create(Student* p, const int N);
void Print(const Student* p, const int N);
int GetThirdMark(const Student& s);
void Sort(Student* p, const int N);
int* IndexSort(const Student* p, const int N);
void PrintIndexSorted(const Student* p, const int* I, const int N);
int BinSearch(const Student* p, const int N, const string prizv, const Specialnist spec, const int thirdMark);

// Вирівнювання кириличного UTF-8 тексту в таблиці
string Pad(const string& s, int w) {
    int len = 0;
    for (char c : s)
        if ((static_cast<unsigned char>(c) & 0xC0) != 0x80) len++;
    return (len < w) ? s + string(static_cast<size_t>(w - len), ' ') : s;
}

#ifndef UNIT_TEST
int main() {
    int N;
    do {
        cout << "Введіть кількість студентів (N > 0): ";
        cin >> N;
    } while (N <= 0);

    Student* p = new Student[static_cast<size_t>(N)];
    int* I = nullptr;

    int menuItem;
    do {
        cout << "\n================ МЕНЮ ================\n";
        cout << " [1] - введення даних з клавіатури\n";
        cout << " [2] - вивід даних на екран\n";
        cout << " [3] - фізичне впорядкування масиву\n";
        cout << " [4] - індексне впорядкування та вивід\n";
        cout << " [5] - бінарний пошук студента\n";
        cout << " [0] - вихід\n";
        cout << "======================================\n";
        cout << "Виберіть дію: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            Sort(p, N);
            cout << "Масив фізично впорядковано!\n";
            break;
        case 4:
            if (I != nullptr) delete[] I;
            I = IndexSort(p, N);
            PrintIndexSorted(p, I, N);
            break;
        case 5: {
            int ispec, mark;
            string prizv;
            cout << "Введіть ключі пошуку:\n";
            do {
                cout << " спеціальність (0 - КН, 1 - Інф, 2 - МЕ, 3 - ФІ, 4 - ТН): ";
                cin >> ispec;
            } while (ispec < 0 || ispec > 4);
            Specialnist spec = (Specialnist)ispec;
            do {
                cout << " оцінка з третього предмету (2-5): ";
                cin >> mark;
            } while (mark < 2 || mark > 5);
            cout << " прізвище: ";
            cin >> ws;
            getline(cin, prizv);

            int found = BinSearch(p, N, prizv, spec, mark);
            if (found != -1)
                cout << "Знайдено студента у позиції № " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено (спочатку виконайте фізичне впорядкування [3]).\n";
            break;
        }
        case 0:
            break;
        default:
            cout << "Помилкове значення! Спробуйте ще раз.\n";
        }
    } while (menuItem != 0);

    if (I != nullptr) delete[] I;
    delete[] p;
    return 0;
}
#endif

int GetThirdMark(const Student& s) {
    switch (s.spec) {
    case KN:
        return s.programuvannya;
    case INF:
        return s.chyselni_metody;
    case ME:
    case FI:
    case TN:
        return s.pedagogika;
    }
    return 0;
}

void Create(Student* p, const int N) {
    int ispec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":\n";

        cout << " прізвище: ";
        cin >> ws;
        getline(cin, p[i].prizv);

        do {
            cout << " курс (1-6): ";
            cin >> p[i].kurs;
        } while (p[i].kurs < 1 || p[i].kurs > 6);

        do {
            cout << " спеціальність (0 - КН, 1 - Інф, 2 - МЕ, 3 - ФІ, 4 - ТН): ";
            cin >> ispec;
        } while (ispec < 0 || ispec > 4);
        p[i].spec = (Specialnist)ispec;

        do {
            cout << " оцінка з фізики (2-5): ";
            cin >> p[i].fizyka;
        } while (p[i].fizyka < 2 || p[i].fizyka > 5);

        do {
            cout << " оцінка з математики (2-5): ";
            cin >> p[i].matematyka;
        } while (p[i].matematyka < 2 || p[i].matematyka > 5);

        switch (p[i].spec) {
        case KN:
            do {
                cout << " оцінка з програмування (2-5): ";
                cin >> p[i].programuvannya;
            } while (p[i].programuvannya < 2 || p[i].programuvannya > 5);
            break;
        case INF:
            do {
                cout << " оцінка з чисельних методів (2-5): ";
                cin >> p[i].chyselni_metody;
            } while (p[i].chyselni_metody < 2 || p[i].chyselni_metody > 5);
            break;
        case ME:
        case FI:
        case TN:
            do {
                cout << " оцінка з педагогіки (2-5): ";
                cin >> p[i].pedagogika;
            } while (p[i].pedagogika < 2 || p[i].pedagogika > 5);
            break;
        }
        cout << endl;
    }
}

void Print(const Student* p, const int N) {
    cout << "=============================================================================================================================" << endl;
    cout << "|  №  | Прізвище      | Курс | Спеціальність           | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1 << " "
             << "| " << Pad(p[i].prizv, 13)
             << " | " << setw(4) << right << p[i].kurs
             << " | " << Pad(specStr[p[i].spec], 23)
             << " | " << setw(6) << right << p[i].fizyka
             << " | " << setw(10) << right << p[i].matematyka;

        switch (p[i].spec) {
        case KN:
            cout << " | " << setw(13) << right << p[i].programuvannya
                 << " | " << setw(15) << right << " "
                 << " | " << setw(10) << right << " " << " |" << endl;
            break;
        case INF:
            cout << " | " << setw(13) << right << " "
                 << " | " << setw(15) << right << p[i].chyselni_metody
                 << " | " << setw(10) << right << " " << " |" << endl;
            break;
        case ME:
        case FI:
        case TN:
            cout << " | " << setw(13) << right << " "
                 << " | " << setw(15) << right << " "
                 << " | " << setw(10) << right << p[i].pedagogika << " |" << endl;
            break;
        }
    }
    cout << "=============================================================================================================================" << endl << endl;
}

void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            int m1 = GetThirdMark(p[i1]);
            int m2 = GetThirdMark(p[i1 + 1]);
            if ((specStr[p[i1].spec] > specStr[p[i1 + 1].spec]) ||
                (specStr[p[i1].spec] == specStr[p[i1 + 1].spec] && m1 > m2) ||
                (specStr[p[i1].spec] == specStr[p[i1 + 1].spec] && m1 == m2 && p[i1].prizv > p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
        }
}

int* IndexSort(const Student* p, const int N) {
    int* I = new int[static_cast<size_t>(N)];
    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    for (i = 1; i < N; i++) {
        value = I[i];
        int mVal = GetThirdMark(p[value]);
        for (j = i - 1;
             j >= 0 && ((specStr[p[I[j]].spec] > specStr[p[value].spec]) ||
                        (specStr[p[I[j]].spec] == specStr[p[value].spec] && GetThirdMark(p[I[j]]) > mVal) ||
                        (specStr[p[I[j]].spec] == specStr[p[value].spec] && GetThirdMark(p[I[j]]) == mVal && p[I[j]].prizv > p[value].prizv));
             j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(const Student* p, const int* I, const int N) {
    cout << "=============================================================================================================================" << endl;
    cout << "|  №  | Прізвище      | Курс | Спеціальність           | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        int k = I[i];
        cout << "| " << setw(3) << right << i + 1 << " "
             << "| " << Pad(p[k].prizv, 13)
             << " | " << setw(4) << right << p[k].kurs
             << " | " << Pad(specStr[p[k].spec], 23)
             << " | " << setw(6) << right << p[k].fizyka
             << " | " << setw(10) << right << p[k].matematyka;

        switch (p[k].spec) {
        case KN:
            cout << " | " << setw(13) << right << p[k].programuvannya
                 << " | " << setw(15) << right << " "
                 << " | " << setw(10) << right << " " << " |" << endl;
            break;
        case INF:
            cout << " | " << setw(13) << right << " "
                 << " | " << setw(15) << right << p[k].chyselni_metody
                 << " | " << setw(10) << right << " " << " |" << endl;
            break;
        case ME:
        case FI:
        case TN:
            cout << " | " << setw(13) << right << " "
                 << " | " << setw(15) << right << " "
                 << " | " << setw(10) << right << p[k].pedagogika << " |" << endl;
            break;
        }
    }
    cout << "=============================================================================================================================" << endl << endl;
}

int BinSearch(const Student* p, const int N, const string prizv, const Specialnist spec, const int thirdMark) {
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
        } else {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
