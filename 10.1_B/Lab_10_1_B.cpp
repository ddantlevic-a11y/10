// Lab_10_1_B.cpp
// Данилевич Данило
// Лабораторна робота № 10.1 (Рівень В)
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
double CalcAverage(const Student& s);
void PrintAverages(const Student* p, const int N);
double PercentPhysics45(const Student* p, const int N);

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
        if (N <= 0) cout << "Помилка! Кількість має бути більшою за 0.\n";
    } while (N <= 0);

    Student* p = new Student[static_cast<size_t>(N)];

    Create(p, N);
    Print(p, N);

    PrintAverages(p, N);
    double proc = PercentPhysics45(p, N);
    cout << "Процент студентів, які отримали з фізики оцінки \"5\" або \"4\": "
         << fixed << setprecision(2) << proc << "%" << endl;

    delete[] p;
    return 0;
}
#endif

void Create(Student* p, const int N) {
    int ispec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;

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

double CalcAverage(const Student& s) {
    int thirdMark = 0;
    if (s.spec == KN) thirdMark = s.programuvannya;
    else if (s.spec == INF) thirdMark = s.chyselni_metody;
    else thirdMark = s.pedagogika;
    return (s.fizyka + s.matematyka + thirdMark) / 3.0;
}

void PrintAverages(const Student* p, const int N) {
    cout << "Середній бал кожного студента:" << endl;
    cout << "-----------------------------------" << endl;
    cout << "|  №  | Прізвище      | Сер. бал  |" << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << right << i + 1 << " "
             << "| " << Pad(p[i].prizv, 13)
             << " | " << setw(9) << fixed << setprecision(2) << right << CalcAverage(p[i]) << " |" << endl;
    }
    cout << "-----------------------------------" << endl << endl;
}

double PercentPhysics45(const Student* p, const int N) {
    if (N == 0) return 0.0;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (p[i].fizyka == 5 || p[i].fizyka == 4) {
            count++;
        }
    }
    return (100.0 * count) / N;
}
