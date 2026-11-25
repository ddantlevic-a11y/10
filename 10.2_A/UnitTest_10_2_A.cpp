// UnitTest_10_2_A.cpp
// Данилевич Данило
// Модульний тест для Lab_10_2_A

#include <iostream>
#include <cassert>

#define UNIT_TEST
#include "Lab_10_2_A.cpp"

void TestSortAndBinSearch()
{
    const int N = 4;
    Student arr[N] = {
        { "Яковенко", 1, KN,  4, 4, 5 },
        { "Бойко",    2, INF, 5, 5, 4 },
        { "Авраменко",3, KN,  3, 4, 5 },
        { "Мельник",  1, KN,  5, 5, 3 }
    };

    // Перевірка індексного впорядкування без зміни оригіналу
    int* I = IndexSort(arr, N);
    // Порядок назв спеціальностей: "Інформатика" (INF) < "Комп'ютерні науки" (KN)
    assert(arr[I[0]].prizv == "Бойко");     // INF, 4
    assert(arr[I[1]].prizv == "Мельник");   // KN, 3
    assert(arr[I[2]].prizv == "Авраменко"); // KN, 5, Авраменко
    assert(arr[I[3]].prizv == "Яковенко");  // KN, 5, Яковенко
    delete[] I;

    // Фізичне впорядкування
    Sort(arr, N);
    assert(arr[0].prizv == "Бойко");
    assert(arr[1].prizv == "Мельник");
    assert(arr[2].prizv == "Авраменко");
    assert(arr[3].prizv == "Яковенко");

    // Бінарний пошук
    assert(BinSearch(arr, N, "Авраменко", KN, 5) == 2);
    assert(BinSearch(arr, N, "Бойко", INF, 4) == 0);
    assert(BinSearch(arr, N, "Невідомий", KN, 5) == -1);

    cout << "Test 1 (IndexSort, Sort, BinSearch) passed successfully!" << endl;
}

int main()
{
    TestSortAndBinSearch();
    cout << "\nAll Unit Tests for Lab 10.2 (Level A) passed successfully!" << endl;
    return 0;
}
