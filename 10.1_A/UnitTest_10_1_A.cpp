// UnitTest_10_1_A.cpp
// Данилевич Данило
// Модульний тест для Lab_10_1_A

#include <iostream>
#include <cassert>
#include <cmath>

#define UNIT_TEST
#include "Lab_10_1_A.cpp"

void TestCalcAverage()
{
    Student s1 = { "Іваненко", 1, KN, 5, 4, 5 };
    assert(fabs(CalcAverage(s1) - 14.0 / 3.0) < 1e-6);

    Student s2 = { "Петренко", 2, INF, 3, 3, 3 };
    assert(fabs(CalcAverage(s2) - 3.0) < 1e-6);

    cout << "Test 1 (CalcAverage) passed successfully!" << endl;
}

void TestPercentPhysics45()
{
    Student arr[4] = {
        { "Іваненко",  1, KN, 5, 4, 5 },
        { "Петренко",  2, INF, 4, 3, 4 },
        { "Сидоренко", 3, ME, 3, 5, 4 },
        { "Коваленко", 1, FI, 2, 3, 3 }
    };
    double proc = PercentPhysics45(arr, 4);
    assert(fabs(proc - 50.0) < 1e-6);

    Student arrAll[2] = {
        { "Авраменко", 1, KN, 5, 5, 5 },
        { "Бойко",     2, TN, 4, 4, 4 }
    };
    assert(fabs(PercentPhysics45(arrAll, 2) - 100.0) < 1e-6);

    cout << "Test 2 (PercentPhysics45) passed successfully!" << endl;
}

int main()
{
    TestCalcAverage();
    TestPercentPhysics45();

    cout << "\nAll Unit Tests for Lab 10.1 (Level A) passed successfully!" << endl;
    return 0;
}
