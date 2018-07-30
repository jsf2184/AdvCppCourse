//
// Section 4 Lesson 13 - Vectors And Memory
//


#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

namespace {

    TEST(StlVector, CapacityTest) {

        vector<double> numbers(0);

        auto size = numbers.size();
        auto capacity = numbers.capacity();
        cout << "Size: " << size << endl;
        cout << "Capacity: " << capacity << endl;

        for (int i = 0; i < 10000; i++) {
            if (numbers.capacity() != capacity) {
                capacity = numbers.capacity();
                cout << "Capacity change at element: " << i << ", capacity = " << capacity << endl;
            }
            numbers.push_back(i);
        }

        numbers.reserve(100000);
        cout << numbers[2] << endl;
        cout << "Size: " << numbers.size() << endl;
        cout << "Capacity: " << numbers.capacity() << endl;
    }
}