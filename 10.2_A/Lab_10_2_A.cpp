// Lab_10_2_A.cpp
// Данилевич Данило
// Лабораторна робота № 10.2 (Рівень А)
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
    int informatyka;
};

void Create(Student* p, const int N);
void Print(const Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(const Student* p, const int N);
void PrintIndexSorted(const Student* p, const int* I, const int N);
int BinSearch(const Student* p, const int N, const string prizv, const Specialnist spec, const int infMark);

#ifndef UNIT_TEST
int main() {
    int N;
    do {
        cout << "Vvedit kilkist studentiv (N > 0): ";
        cin >> N;
    } while (N <= 0);

    Student* p = new Student[static_cast<size_t>(N)];
    int* I = nullptr;

    int menuItem;
    do {
        cout << "\n================ MENYU ================\n";
        cout << " [1] - vvedennya danykh z klaviatury\n";
        cout << " [2] - vyvid danykh na ekran\n";
        cout << " [3] - fizychne vporyadkuvannya masyvu\n";
        cout << " [4] - indeksne vporyadkuvannya ta vyvid\n";
        cout << " [5] - binarnyy poshuk studenta\n";
        cout << " [0] - vykhid\n";
        cout << "=======================================\n";
        cout << "Vyberit diyu: ";
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
            cout << "Masyv fizychno vporyadkovano!\n";
            break;
        case 4:
            if (I != nullptr) delete[] I;
            I = IndexSort(p, N);
            PrintIndexSorted(p, I, N);
            break;
        case 5: {
            int ispec, mark;
            string prizv;
            cout << "Vvedit klyuchi poshuku:\n";
            do {
                cout << " spetsialnist (0 - KN, 1 - INF, 2 - ME, 3 - FI, 4 - TN): ";
                cin >> ispec;
            } while (ispec < 0 || ispec > 4);
            Specialnist spec = (Specialnist)ispec;
            do {
                cout << " otsinka z informatyky (2-5): ";
                cin >> mark;
            } while (mark < 2 || mark > 5);
            cout << " prizvyshche: ";
            cin >> ws;
            getline(cin, prizv);

            int found = BinSearch(p, N, prizv, spec, mark);
            if (found != -1)
                cout << "Znaydeno studenta u pozytsiyi # " << found + 1 << endl;
            else
                cout << "Shukanoho studenta ne znaydeno (spochatku vykonayte fizychne vporyadkuvannya [3]).\n";
            break;
        }
        case 0:
            break;
        default:
            cout << "Pomylkove znachennya! Sprobuite shche raz.\n";
        }
    } while (menuItem != 0);

    if (I != nullptr) delete[] I;
    delete[] p;
    return 0;
}
#endif

void Create(Student* p, const int N) {
    int ispec;
    for (int i = 0; i < N; i++) {
        cout << "Student # " << i + 1 << ":\n";

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

        do {
            cout << " otsinka z informatyky (2-5): ";
            cin >> p[i].informatyka;
        } while (p[i].informatyka < 2 || p[i].informatyka > 5);

        cout << endl;
    }
}

void Print(const Student* p, const int N) {
    cout << "=====================================================================" << endl;
    cout << "| # | Prizvyshche   | Kurs | Spetsialnist  | Fiz. | Mat. | Inform. |" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << right << i + 1 << " "
             << "| " << setw(13) << left << p[i].prizv
             << " | " << setw(4) << right << p[i].kurs
             << " | " << setw(13) << left << specStr[p[i].spec]
             << " | " << setw(4) << right << p[i].fizyka
             << " | " << setw(4) << right << p[i].matematyka
             << " | " << setw(7) << right << p[i].informatyka << " |" << endl;
    }
    cout << "=====================================================================" << endl << endl;
}

void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((specStr[p[i1].spec] > specStr[p[i1 + 1].spec]) ||
                (specStr[p[i1].spec] == specStr[p[i1 + 1].spec] && p[i1].informatyka > p[i1 + 1].informatyka) ||
                (specStr[p[i1].spec] == specStr[p[i1 + 1].spec] && p[i1].informatyka == p[i1 + 1].informatyka && p[i1].prizv > p[i1 + 1].prizv))
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* IndexSort(const Student* p, const int N) {
    int* I = new int[static_cast<size_t>(N)];
    for (int i = 0; i < N; i++)
        I[i] = i;

    int i, j, value;
    for (i = 1; i < N; i++) {
        value = I[i];
        for (j = i - 1;
             j >= 0 && ((specStr[p[I[j]].spec] > specStr[p[value].spec]) ||
                        (specStr[p[I[j]].spec] == specStr[p[value].spec] && p[I[j]].informatyka > p[value].informatyka) ||
                        (specStr[p[I[j]].spec] == specStr[p[value].spec] && p[I[j]].informatyka == p[value].informatyka && p[I[j]].prizv > p[value].prizv));
             j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(const Student* p, const int* I, const int N) {
    cout << "=====================================================================" << endl;
    cout << "| # | Prizvyshche   | Kurs | Spetsialnist  | Fiz. | Mat. | Inform. |" << endl;
    cout << "---------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << right << i + 1 << " "
             << "| " << setw(13) << left << p[I[i]].prizv
             << " | " << setw(4) << right << p[I[i]].kurs
             << " | " << setw(13) << left << specStr[p[I[i]].spec]
             << " | " << setw(4) << right << p[I[i]].fizyka
             << " | " << setw(4) << right << p[I[i]].matematyka
             << " | " << setw(7) << right << p[I[i]].informatyka << " |" << endl;
    }
    cout << "=====================================================================" << endl << endl;
}

int BinSearch(const Student* p, const int N, const string prizv, const Specialnist spec, const int infMark) {
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].spec == spec && p[m].informatyka == infMark && p[m].prizv == prizv)
            return m;
        if ((specStr[p[m].spec] < specStr[spec]) ||
            (specStr[p[m].spec] == specStr[spec] && p[m].informatyka < infMark) ||
            (specStr[p[m].spec] == specStr[spec] && p[m].informatyka == infMark && p[m].prizv < prizv))
        {
            L = m + 1;
        } else {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
