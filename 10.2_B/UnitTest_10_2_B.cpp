// UnitTest_10_2_B.cpp
// Данилевич Данило
// Модульний тест для Lab_10_2_B

#include <iostream>
#include <cassert>

#define UNIT_TEST
#include "Lab_10_2_B.cpp"

void TestSortAndBinSearch()
{
    const int N = 4;
    Student arr[N] = {
        { "Яковенко",  1, KN,  4, 4, { 5 } },
        { "Бойко",     2, INF, 5, 5, { 4 } },
        { "Авраменко", 3, KN,  3, 4, { 5 } },
        { "Мельник",   1, ME,  5, 5, { 3 } }
    };

    // Порядок назв спеціальностей:
    // "Інформатика" (INF) < "Комп'ютерні науки" (KN) < "Математика та економіка" (ME)
    int* I = IndexSort(arr, N);
    assert(arr[I[0]].prizv == "Бойко");     // INF
    assert(arr[I[1]].prizv == "Авраменко"); // KN, 5, Авраменко
    assert(arr[I[2]].prizv == "Яковенко");  // KN, 5, Яковенко
    assert(arr[I[3]].prizv == "Мельник");   // ME
    delete[] I;

    Sort(arr, N);
    assert(arr[0].prizv == "Бойко");
    assert(arr[1].prizv == "Авраменко");
    assert(arr[2].prizv == "Яковенко");
    assert(arr[3].prizv == "Мельник");

    assert(BinSearch(arr, N, "Яковенко", KN, 5) == 2);
    assert(BinSearch(arr, N, "Мельник", ME, 3) == 3);
    assert(BinSearch(arr, N, "Іваненко", INF, 4) == -1);

    cout << "Test 1 (IndexSort, Sort, BinSearch) passed successfully!" << endl;
}

int main()
{
    TestSortAndBinSearch();
    cout << "\nAll Unit Tests for Lab 10.2 (Level B) passed successfully!" << endl;
    return 0;
}
