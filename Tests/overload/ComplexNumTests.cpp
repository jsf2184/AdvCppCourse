//
// Created by Jeffrey on 5/26/2018.
//
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "ComplexNum.h"

namespace jsf2184 {

    TEST(ComplexNumTests, basics) {
        ComplexNum c1(10.0, 3.9);
        cout << endl << "hello " << c1 << " there" << endl;
    }

    TEST(ComplexNumTests, testAdd) {
        ComplexNum c1(10.0, 3.9);
        ComplexNum c2(1.0, 0.1);
        ComplexNum c3 = c1 + c2;
        cout
                << endl
                << "c1: "
                << c1
                << " c2: "
                << c2
                << " c3: "
                << c3
                << endl;
        cout << ComplexNum(8, 1) + 3 << endl;
        cout << 3.0 + ComplexNum(8, 1) << endl;

    }

    TEST(ComplexNumTests, testEquals) {
        ComplexNum c1(10.0, 3.9);
        ComplexNum c2(1.0, 0.1);
        ComplexNum c3(10.0, 3.9);
        cout
                << endl
                << "c1 == c2: "
                << (c1 == c2) << endl
                << "c1 != c2: "
                << (c1 != c2) << endl
                << "c1 == c3: "
                << (c1 == c3)  << endl
                << "c1 != c3: "
                << (c1 != c3)
                << endl;

    }


}