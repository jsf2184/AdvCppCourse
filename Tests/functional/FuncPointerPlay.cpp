//
// Section 7 Lesson 34 - Function Pointers
//


#include <iostream>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;


namespace  jsf2184 {

    void printHi(int x) {
        cout << "hi: "  << x << endl;
    }

    void printBye(int x) {
        cout << "bye: " << x <<  endl;
    }


    TEST(FuncPointer, invokeDirectly) {
        cout << endl;

        // pFunc is a pointer to a function that takes an int and returns void
        void ( * pFunc)(int);

        pFunc = &printHi;
        (*pFunc)(3);
        pFunc = printBye;  // Note & in front of func is optional.
        pFunc(3);          // And the (*pFunc) is optional too
    }

    void caller( void (*pFunc)(int), int x) {
        pFunc(x);
    }

    TEST(FuncPointer, invokeFromCaller) {
        cout << endl;
        // pFunc is a pointer to a function that takes an int and returns void
        caller(printHi, 3);
        caller(printBye, 4);
    }

    template<typename T>
    void populateVector(vector<T> &vec, T (*pFunc)(int), int count) {
        for (int i=0; i<count; i++) {
            vec.push_back(pFunc(i));
        }
    }

    template<typename T>
    void printVector(vector<T> &vec) {
        for(auto it = vec.begin(); it < vec.end(); it++) {
            cout << *it << endl;
        }
    }


    TEST(FuncPointer, popVectorWithStringsByFuncCreator) {
        vector<string> vec;
        populateVector(vec, to_string, 3);
        cout << endl;
        printVector(vec);
    }


    TEST(FuncPointer, popVectorWithClassByFuncCreator) {
        vector<C> vec;
        populateVector(vec, C::createC, 3);
        cout << endl;
        printVector(vec);
    }


    int identity(int x) { return x;}
    bool isEven(int x) {
        return x %2 == 0;
    }
    TEST(FuncPointer, applyFuncToVector) {
        cout << endl;
        vector<int> vec;
        populateVector(vec, identity, 10);
        printVector(vec);
        const long res = count_if(vec.begin(), vec.end(), isEven);
        cout << "vec has " << res << " even numbers" << endl;
    }




}