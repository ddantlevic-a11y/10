// Lab_10_1_B.cpp
// Данилевич Данило
// Лабораторна робота № 10.1 (Рівень В)
// Варіант 7

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum Specialnist { KN, INF, ME, FI, TN };
string specStr[] = { "Komp. nauky", "Informatyka", "Mat. ta ek.", "Fiz. ta inf.", "Trud. navch." };

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

#ifndef UNIT_TEST
int main() {
    int N;
    do {
        cout << "Vvedit kilkist studentiv (N > 0): ";
        cin >> N;
        if (N <= 0) cout << "Pomylka! Kilkist maye buty bilshoyu za 0.\n";
    } while (N <= 0);

    Student* p = new Student[static_cast<size_t>(N)];

    Create(p, N);
    Print(p, N);

    PrintAverages(p, N);
    double proc = PercentPhysics45(p, N);
    cout << "Protsent studentiv, yaki otrymaly z fizyky otsinky \"5\" abo \"4\": "
         << fixed << setprecision(2) << proc << "%" << endl;

    delete[] p;
    return 0;
}
#endif

void Create(Student* p, const int N) {
    int ispec;
    for (int i = 0; i < N; i++) {
        cout << "Student # " << i + 1 << ":" << endl;

        cout << " prizvyshche: ";
        cin >> ws;
        getline(cin, p[i].prizv);

        do {
            cout << " kurs (1-6): ";
            cin >> p[i].kurs;
        } while (p[i].kurs < 1 || p[i].kurs > 6);

        do {
            cout << " spetsialnist (0 - KN, 1 - INF, 2 - ME, 3 - FI, 4 - TN): ";
            cin >> ispec;
        } while (ispec < 0 || ispec > 4);
        p[i].spec = (Specialnist)ispec;

        do {
            cout << " otsinka z fizyky (2-5): ";
            cin >> p[i].fizyka;
        } while (p[i].fizyka < 2 || p[i].fizyka > 5);

        do {
            cout << " otsinka z matematyky (2-5): ";
            cin >> p[i].matematyka;
        } while (p[i].matematyka < 2 || p[i].matematyka > 5);

        switch (p[i].spec) {
        case KN:
            do {
                cout << " otsinka z programuvannya (2-5): ";
                cin >> p[i].programuvannya;
            } while (p[i].programuvannya < 2 || p[i].programuvannya > 5);
            break;
        case INF:
            do {
                cout << " otsinka z chyselnykh metodiv (2-5): ";
                cin >> p[i].chyselni_metody;
            } while (p[i].chyselni_metody < 2 || p[i].chyselni_metody > 5);
            break;
        case ME:
        case FI:
        case TN:
            do {
                cout << " otsinka z pedagogiky (2-5): ";
                cin >> p[i].pedagogika;
            } while (p[i].pedagogika < 2 || p[i].pedagogika > 5);
            break;
        }
        cout << endl;
    }
}

void Print(const Student* p, const int N) {
    cout << "==========================================================================================" << endl;
    cout << "| # | Prizvyshche   | Kurs | Spetsialnist  | Fiz. | Mat. | Prog. | Chys.met | Pedagogika |" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << right << i + 1 << " "
             << "| " << setw(13) << left << p[i].prizv
             << " | " << setw(4) << right << p[i].kurs
             << " | " << setw(13) << left << specStr[p[i].spec]
             << " | " << setw(4) << right << p[i].fizyka
             << " | " << setw(4) << right << p[i].matematyka;

        switch (p[i].spec) {
        case KN:
            cout << " | " << setw(5) << right << p[i].programuvannya
                 << " | " << setw(8) << right << " "
                 << " | " << setw(10) << right << " " << " |" << endl;
            break;
        case INF:
            cout << " | " << setw(5) << right << " "
                 << " | " << setw(8) << right << p[i].chyselni_metody
                 << " | " << setw(10) << right << " " << " |" << endl;
            break;
        case ME:
        case FI:
        case TN:
            cout << " | " << setw(5) << right << " "
                 << " | " << setw(8) << right << " "
                 << " | " << setw(10) << right << p[i].pedagogika << " |" << endl;
            break;
        }
    }
    cout << "==========================================================================================" << endl << endl;
}

double CalcAverage(const Student& s) {
    int thirdMark = 0;
    if (s.spec == KN) thirdMark = s.programuvannya;
    else if (s.spec == INF) thirdMark = s.chyselni_metody;
    else thirdMark = s.pedagogika;
    return (s.fizyka + s.matematyka + thirdMark) / 3.0;
}

void PrintAverages(const Student* p, const int N) {
    cout << "Seredniy bal kozhnoho studenta:" << endl;
    cout << "---------------------------------" << endl;
    cout << "| # | Prizvyshche   | Ser. bal  |" << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << right << i + 1 << " "
             << "| " << setw(13) << left << p[i].prizv
             << " | " << setw(9) << fixed << setprecision(2) << right << CalcAverage(p[i]) << " |" << endl;
    }
    cout << "---------------------------------" << endl << endl;
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
