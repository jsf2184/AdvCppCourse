//
// Section 8 Lesson 39- DeclType and TypeID
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <typeinfo>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;
using  jsf2184::C;

namespace jsf2184 {
    TEST(NewLoop, forEachCharPtr) {
        cout << endl;
        const char *names[] = {"Bob", "Joe", "Sam"};
        for (auto n : names) {
            cout << "type: " << typeid(n).name() << " value: "  << n << endl;
        }
    }
    TEST(NewLoop, forEachString) {
        cout << endl;
        string names[] = {"Bob", "Joe", "Sam"};
        for (auto n : names) {
            cout << "type: " << typeid(n).name() << " value: "  << n << endl;
        }
    }

    TEST(NewLoop, forEachInt) {
        cout << endl;
        auto values = {1, 2, 3};
        for (auto n : values) {
            cout << "type: " << typeid(n).name() << " value: "  << n << endl;
        }
    }

    TEST(NewLoop, forEachVector) {
        cout << endl;
        vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        for (auto n : vec) {
            cout << "type: " << typeid(n).name() << " value: "  << n << endl;
        }

        for (auto it = vec.begin(); it != vec.end(); it++) {
            cout << "type: " << typeid(*it).name() << " value: "  << *it << endl;

        }
    }

    TEST(NewLoop, forEachCharsInCharArray) {
        cout << endl;
        char str[] = "abc";
        for (auto n : str) {
            cout << "type: " << typeid(n).name() << " value: "  << n << endl;
        }
    }

    TEST(NewLoop, forEachCharsInStr) {
        cout << endl;
        string str = "abc";
        for (auto n : str) {
            cout << "type: " << typeid(n).name() << " value: "  << n << endl;
        }
    }


}