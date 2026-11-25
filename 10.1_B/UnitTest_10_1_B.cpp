// UnitTest_10_1_B.cpp
// Данилевич Данило
// Модульний тест для Lab_10_1_B

#include <iostream>
#include <cassert>
#include <cmath>

#define UNIT_TEST
#include "Lab_10_1_B.cpp"

void TestCalcAverage()
{
    Student s1;
    s1.prizv = "Іваненко";
    s1.kurs = 1;
    s1.spec = KN;
    s1.fizyka = 5;
    s1.matematyka = 4;
    s1.programuvannia = 5;
    assert(fabs(CalcAverage(s1) - 14.0 / 3.0) < 1e-6);

    Student s2;
    s2.prizv = "Петренко";
    s2.kurs = 2;
    s2.spec = INF;
    s2.fizyka = 4;
    s2.matematyka = 3;
    s2.chyselni_metody = 5;
    assert(fabs(CalcAverage(s2) - 4.0) < 1e-6);

    Student s3;
    s3.prizv = "Сидоренко";
    s3.kurs = 3;
    s3.spec = ME;
    s3.fizyka = 3;
    s3.matematyka = 3;
    s3.pedahohika = 3;
    assert(fabs(CalcAverage(s3) - 3.0) < 1e-6);

    cout << "Test 1 (CalcAverage) passed successfully!" << endl;
}

void TestPercentPhysics45()
{
    Student arr[3];
    arr[0] = { "Іваненко", 1, KN, 5, 4, { 5 } };
    arr[1] = { "Петренко", 2, INF, 4, 3, { 4 } };
    arr[2] = { "Сидоренко", 3, TN, 3, 5, { 4 } };

    double proc = PercentPhysics45(arr, 3);
    assert(fabs(proc - (200.0 / 3.0)) < 1e-6);

    cout << "Test 2 (PercentPhysics45) passed successfully!" << endl;
}

int main()
{
    TestCalcAverage();
    TestPercentPhysics45();

    cout << "\nAll Unit Tests for Lab 10.1 (Level B) passed successfully!" << endl;
    return 0;
}
