// UnitTest_10_3.cpp
// Данилевич Данило
// Модульний тест для Lab_10_3

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdio>

#define UNIT_TEST
#include "Lab_10_3.cpp"

void TestAddRemoveSort()
{
    int N = 2;
    Tovar* arr = new Tovar[N]{
        { "Цукор", "АТБ",    35.50, 100, "упаковка по 20 кг." },
        { "Борошно", "Сільпо", 28.00, 50, "мішок 10 кг." }
    };

    AddTovar(arr, N, { "Олія", "АТБ", 65.00, 30, "пляшка 1 л." });
    assert(N == 3);
    assert(arr[2].nazva == "Олія");

    SortByNazva(arr, N);
    assert(arr[0].nazva == "Борошно");
    assert(arr[1].nazva == "Олія");
    assert(arr[2].nazva == "Цукор");

    SortByMahazyn(arr, N);
    assert(arr[0].mahazyn == "АТБ");
    assert(arr[2].mahazyn == "Сільпо");

    assert(RemoveTovar(arr, N, 1) == true);
    assert(N == 2);

    delete[] arr;
    cout << "Test 1 (Add, Sort, Remove) passed successfully!" << endl;
}

void TestFileSaveLoad()
{
    int N = 2;
    Tovar* arr = new Tovar[N]{
        { "Молоко", "Близенько", 42.50, 20, "пакет 1 л." },
        { "Хліб",   "Рукавичка", 24.00, 40, "шт." }
    };

    const char* fname = "test_tovar.bin";
    assert(SaveToFile(arr, N, fname) == true);

    Tovar* loaded = nullptr;
    int loadedN = 0;
    assert(LoadFromFile(loaded, loadedN, fname) == true);
    assert(loadedN == 2);
    assert(loaded[0].nazva == "Молоко");
    assert(loaded[0].mahazyn == "Близенько");
    assert(fabs(loaded[0].vartist - 42.50) < 1e-6);
    assert(loaded[1].nazva == "Хліб");
    assert(loaded[1].odynytsia == "шт.");

    remove(fname);
    delete[] arr;
    delete[] loaded;
    cout << "Test 2 (SaveToFile, LoadFromFile) passed successfully!" << endl;
}

int main()
{
    TestAddRemoveSort();
    TestFileSaveLoad();
    cout << "\nAll Unit Tests for Lab 10.3 passed successfully!" << endl;
    return 0;
}
