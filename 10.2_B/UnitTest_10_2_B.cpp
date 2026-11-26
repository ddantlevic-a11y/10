// UnitTest_10_2_B.cpp
// Данилевич Данило

#include <iostream>
#include <cassert>

#define UNIT_TEST
#include "Lab_10_2_B.cpp"

void TestSortAndBinSearch() {
    const int N = 4;
    Student arr[N] = {
        { "Yakovenko", 1, KN,  4, 4, { 5 } },
        { "Boyko",     2, INF, 5, 5, { 4 } },
        { "Avramenko", 3, KN,  3, 4, { 5 } },
        { "Melnyk",    1, ME,  5, 5, { 3 } }
    };

    // "Informatyka" (INF) < "Komp. nauky" (KN) < "Mat. ta ek." (ME)
    int* I = IndexSort(arr, N);
    assert(arr[I[0]].prizv == "Boyko");
    assert(arr[I[1]].prizv == "Avramenko");
    assert(arr[I[2]].prizv == "Yakovenko");
    assert(arr[I[3]].prizv == "Melnyk");
    delete[] I;

    Sort(arr, N);
    assert(arr[0].prizv == "Boyko");
    assert(arr[1].prizv == "Avramenko");
    assert(arr[2].prizv == "Yakovenko");
    assert(arr[3].prizv == "Melnyk");

    assert(BinSearch(arr, N, "Yakovenko", KN, 5) == 2);
    assert(BinSearch(arr, N, "Melnyk", ME, 3) == 3);
    assert(BinSearch(arr, N, "Ivanenko", INF, 4) == -1);

    cout << "Test 1 (IndexSort, Sort, BinSearch) passed successfully!" << endl;
}

int main() {
    TestSortAndBinSearch();
    cout << "\nAll Unit Tests for Lab 10.2 (Level B) passed successfully!" << endl;
    return 0;
}
