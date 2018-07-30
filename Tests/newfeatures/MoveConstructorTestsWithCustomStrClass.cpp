//
// Created by Jeffrey on 5/28/2018.
//
#include <iostream>
#include <map>
#include <string>
#include <gtest/gtest.h>
#include "../../Str.h"

using namespace std;

namespace jsf2184 {

    // some perfect forwarding tests.

    TEST(StrTests, SimpleConstructor) {
        cout << endl << "SimpleConstructor Test" << endl;
        Str hi("hello");
        cout << endl << hi << endl;
        EXPECT_TRUE(hi == "hello");

        hi = "hi";
        EXPECT_TRUE(hi == "hi");

    }


    TEST(StrTests, MoveAssignment) {
        cout << endl << "MoveAssignment Test" << endl;
        Str hi("hello");
        hi = Str("hi");
        cout << endl << "done with Test" << endl;

    }
}
