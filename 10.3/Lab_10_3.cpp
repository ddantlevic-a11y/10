// Lab_10_3.cpp
// Данилевич Данило
// Лабораторна робота № 10.3
// Опрацювання масиву структур
// Варіант 7

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Tovar
{
    string nazva;
    string mahazyn;
    double vartist;
    double kilkist;
    string odynytsia;
};

int Utf8Length(const string& s)
{
    int len = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80)
            len++;
    return len;
}

string PadLeft(const string& s, int width)
{
    int len = Utf8Length(s);
    if (len >= width)
        return s;
    return s + string(width - len, ' ');
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

double InputDouble(const string& prompt, double minVal)
{
    double val;
    while (true)
    {
        cout << prompt;
        if (cin >> val && val >= minVal)
            return val;
        cout << "Помилка! Введіть дійсне число >= " << minVal << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void InputOneTovar(Tovar& t)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "    назва товару: ";
    getline(cin, t.nazva);
    cout << "    назва магазину: ";
    getline(cin, t.mahazyn);
    t.vartist = InputDouble("    вартість одиниці (грн): ", 0.01);
    t.kilkist = InputDouble("    кількість: ", 0.01);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "    одиниця вимірювання (напр. шт., упаковка по 20 кг.): ";
    getline(cin, t.odynytsia);
}

void Create(Tovar* p, const int N)
{
    for (int i = 0; i < N; i++)
    {
        cout << "Товар № " << i + 1 << ":" << endl;
        InputOneTovar(p[i]);
        cout << endl;
    }
}

void PrintHeader()
{
    cout << "======================================================================================================" << endl;
    cout << "|  №  |    Назва товару    |      Магазин      | Вартість (грн) | Кількість |   Одиниця вимірювання  |" << endl;
    cout << "------------------------------------------------------------------------------------------------------" << endl;
}

void PrintRow(const Tovar& t, int index)
{
    cout << "| " << setw(3) << right << index << " "
         << "| " << PadLeft(t.nazva, 19)
         << "| " << PadLeft(t.mahazyn, 18)
         << "| " << setw(14) << fixed << setprecision(2) << right << t.vartist << " "
         << "| " << setw(9) << fixed << setprecision(2) << right << t.kilkist << " "
         << "| " << PadLeft(t.odynytsia, 23) << "|" << endl;
}

void Print(const Tovar* p, const int N)
{
    if (N == 0)
    {
        cout << "Список товарів порожній." << endl << endl;
        return;
    }
    PrintHeader();
    for (int i = 0; i < N; i++)
        PrintRow(p[i], i + 1);
    cout << "======================================================================================================" << endl;
    cout << endl;
}

void AddTovar(Tovar*& p, int& N, const Tovar& newTovar)
{
    Tovar* t = new Tovar[N + 1];
    for (int i = 0; i < N; i++)
        t[i] = p[i];
    t[N] = newTovar;
    delete[] p;
    p = t;
    N++;
}

bool RemoveTovar(Tovar*& p, int& N, int index)
{
    if (index < 0 || index >= N)
        return false;

    Tovar* t = (N > 1) ? new Tovar[N - 1] : nullptr;
    int j = 0;
    for (int i = 0; i < N; i++)
    {
        if (i != index)
            t[j++] = p[i];
    }
    delete[] p;
    p = t;
    N--;
    return true;
}

bool EditTovar(Tovar* p, const int N, int index)
{
    if (index < 0 || index >= N)
        return false;
    cout << "Редагування товару № " << index + 1 << ":" << endl;
    InputOneTovar(p[index]);
    return true;
}

void SortByNazva(Tovar* p, const int N)
{
    Tovar tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (p[i1].nazva > p[i1 + 1].nazva)
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

void SortByMahazyn(Tovar* p, const int N)
{
    Tovar tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if (p[i1].mahazyn > p[i1 + 1].mahazyn)
            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int FindByNazva(const Tovar* p, const int N, const string& nazva)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (p[i].nazva == nazva)
        {
            if (count == 0)
                PrintHeader();
            count++;
            PrintRow(p[i], i + 1);
        }
    }
    if (count > 0)
        cout << "======================================================================================================" << endl << endl;
    return count;
}

int FindByMahazyn(const Tovar* p, const int N, const string& mahazyn)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (p[i].mahazyn == mahazyn)
        {
            if (count == 0)
                PrintHeader();
            count++;
            PrintRow(p[i], i + 1);
        }
    }
    if (count > 0)
        cout << "======================================================================================================" << endl << endl;
    return count;
}

void WriteString(ofstream& fout, const string& s)
{
    size_t len = s.size();
    fout.write((char*)&len, sizeof(len));
    if (len > 0)
        fout.write(s.data(), (streamsize)len);
}

void ReadString(ifstream& fin, string& s)
{
    size_t len = 0;
    fin.read((char*)&len, sizeof(len));
    s.resize(len);
    if (len > 0)
        fin.read(&s[0], (streamsize)len);
}

bool SaveToFile(const Tovar* p, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary);
    if (!fout.is_open())
        return false;

    fout.write((char*)&N, sizeof(N));
    for (int i = 0; i < N; i++)
    {
        WriteString(fout, p[i].nazva);
        WriteString(fout, p[i].mahazyn);
        fout.write((char*)&p[i].vartist, sizeof(p[i].vartist));
        fout.write((char*)&p[i].kilkist, sizeof(p[i].kilkist));
        WriteString(fout, p[i].odynytsia);
    }
    fout.close();
    return true;
}

bool LoadFromFile(Tovar*& p, int& N, const char* filename)
{
    ifstream fin(filename, ios::binary);
    if (!fin.is_open())
        return false;

    int newN = 0;
    fin.read((char*)&newN, sizeof(newN));
    if (!fin || newN < 0)
    {
        fin.close();
        return false;
    }

    Tovar* newP = (newN > 0) ? new Tovar[newN] : nullptr;
    for (int i = 0; i < newN; i++)
    {
        ReadString(fin, newP[i].nazva);
        ReadString(fin, newP[i].mahazyn);
        fin.read((char*)&newP[i].vartist, sizeof(newP[i].vartist));
        fin.read((char*)&newP[i].kilkist, sizeof(newP[i].kilkist));
        ReadString(fin, newP[i].odynytsia);
    }
    fin.close();

    delete[] p;
    p = newP;
    N = newN;
    return true;
}

#ifndef UNIT_TEST
int main()
{
    int N = InputInt("Введіть початкову кількість товарів N: ", 1, 100);
    Tovar* p = new Tovar[N];
    Create(p, N);

    int menuItem;
    do {
        cout << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << "  [1]  - вивід списку товарів на екран" << endl;
        cout << "  [2]  - додавання нового товару" << endl;
        cout << "  [3]  - вилучення товару за номером" << endl;
        cout << "  [4]  - редагування товару за номером" << endl;
        cout << "  [5]  - сортування за назвою товару" << endl;
        cout << "  [6]  - сортування за назвою магазину" << endl;
        cout << "  [7]  - пошук товару за назвою" << endl;
        cout << "  [8]  - пошук товарів у вказаному магазині" << endl;
        cout << "  [9]  - запис даних у файл" << endl;
        cout << "  [10] - зчитування даних із файлу" << endl;
        cout << "  [0]  - вихід та завершення роботи програми" << endl << endl;
        menuItem = InputInt("Введіть значення: ", 0, 10);
        cout << endl;

        switch (menuItem)
        {
        case 1:
            Print(p, N);
            break;
        case 2:
        {
            Tovar t;
            cout << "Новий товар:" << endl;
            InputOneTovar(t);
            AddTovar(p, N, t);
            cout << "Товар додано." << endl;
            break;
        }
        case 3:
            if (N == 0)
                cout << "Список порожній!" << endl;
            else
            {
                int idx = InputInt("Введіть номер товару для вилучення (1 - " + to_string(N) + "): ", 1, N);
                RemoveTovar(p, N, idx - 1);
                cout << "Товар вилучено." << endl;
            }
            break;
        case 4:
            if (N == 0)
                cout << "Список порожній!" << endl;
            else
            {
                int idx = InputInt("Введіть номер товару для редагування (1 - " + to_string(N) + "): ", 1, N);
                EditTovar(p, N, idx - 1);
                cout << "Дані оновлено." << endl;
            }
            break;
        case 5:
            SortByNazva(p, N);
            cout << "Список відсортовано за назвою товару." << endl;
            break;
        case 6:
            SortByMahazyn(p, N);
            cout << "Список відсортовано за назвою магазину." << endl;
            break;
        case 7:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string nazva;
            cout << "Введіть назву товару: ";
            getline(cin, nazva);
            if (FindByNazva(p, N, nazva) == 0)
                cout << "Товар з назвою \"" << nazva << "\" не знайдено." << endl;
            break;
        }
        case 8:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string mahazyn;
            cout << "Введіть назву магазину: ";
            getline(cin, mahazyn);
            if (FindByMahazyn(p, N, mahazyn) == 0)
                cout << "Товари в магазині \"" << mahazyn << "\" не знайдено." << endl;
            break;
        }
        case 9:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string filename;
            cout << "Введіть ім'я файлу для запису: ";
            getline(cin, filename);
            if (SaveToFile(p, N, filename.c_str()))
                cout << "Дані успішно збережено у файл \"" << filename << "\"." << endl;
            else
                cout << "Помилка відкриття файлу для запису!" << endl;
            break;
        }
        case 10:
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string filename;
            cout << "Введіть ім'я файлу для зчитування: ";
            getline(cin, filename);
            if (LoadFromFile(p, N, filename.c_str()))
                cout << "Дані успішно зчитано з файлу \"" << filename << "\"." << endl;
            else
                cout << "Помилка відкриття або читання файлу!" << endl;
            break;
        }
        case 0:
            break;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}
#endif
