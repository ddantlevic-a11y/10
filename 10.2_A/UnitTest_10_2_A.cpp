// UnitTest_10_2_A.cpp
// Данилевич Данило

#include <iostream>
#include <cassert>

#define UNIT_TEST
#include "Lab_10_2_A.cpp"

void TestSortAndBinSearch() {
    const int N = 4;
    Student arr[N] = {
        { "Yakovenko", 1, KN,  4, 4, 5 },
        { "Boyko",     2, INF, 5, 5, 4 },
        { "Avramenko", 3, KN,  3, 4, 5 },
        { "Melnyk",    1, KN,  5, 5, 3 }
    };

    // "Informatyka" (INF) < "Komp. nauky" (KN)
    int* I = IndexSort(arr, N);
    assert(arr[I[0]].prizv == "Boyko");
    assert(arr[I[1]].prizv == "Melnyk");
    assert(arr[I[2]].prizv == "Avramenko");
    assert(arr[I[3]].prizv == "Yakovenko");
    delete[] I;

    Sort(arr, N);
    assert(arr[0].prizv == "Boyko");
    assert(arr[1].prizv == "Melnyk");
    assert(arr[2].prizv == "Avramenko");
    assert(arr[3].prizv == "Yakovenko");

    assert(BinSearch(arr, N, "Avramenko", KN, 5) == 2);
    assert(BinSearch(arr, N, "Boyko", INF, 4) == 0);
    assert(BinSearch(arr, N, "Unknown", KN, 5) == -1);

    cout << "Test 1 (IndexSort, Sort, BinSearch) passed successfully!" << endl;
}

int main() {
    TestSortAndBinSearch();
    cout << "\nAll Unit Tests for Lab 10.2 (Level A) passed successfully!" << endl;
    return 0;
}
