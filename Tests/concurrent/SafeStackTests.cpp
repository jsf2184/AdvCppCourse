//
// Following web tutorial at:
// Concurrency Class: Section 2, Lesson 16
////

#include "../../ThreadVector.h"
#include "../../SafeStack.h"
#include <iostream>
#include <gtest/gtest.h>
#include <numeric>
using namespace std;


namespace  jsf2184 {
    TEST(SafeStackTesting, emptyStack) {
        SafeStack sut;
        EXPECT_TRUE(sut.isEmpty());
    }
    TEST(SafeStackTesting, singleThreadPushesAndPops) {
        cout << endl;
        SafeStack sut;
        for (int i=0; i<10; i++) {
            sut.push(i);
        }
        for (int i=9; i >= 0; i--) {
            EXPECT_FALSE(sut.isEmpty());
            auto v = sut.pop();
            cout << "popped off " << v << endl;
            EXPECT_EQ(i, v);
        }
        EXPECT_TRUE(sut.isEmpty());
    }

    TEST(SafeStackTesting, multiThreadPushesAndPops) {
        cout << endl;
        SafeStack sut;
        ThreadVector pushThreadVector;

        // Use 1000 threads to push numbers 0 thru 999 on the SafeStack.
        int n = 1000;
        for (int i=0; i<n; i++) {
            pushThreadVector.push_back([&sut, i]() {sut.push(i);});
        }
        pushThreadVector.join();

        ThreadVector popThreadVector;

        bool poppedValues[n] = {false};

        for (int i=0; i<n; i++) {
            EXPECT_FALSE(poppedValues[i]);
        }

        for (int i=0; i<n; i++) {
            popThreadVector.push_back([&sut, &poppedValues]() {
                // pop one off the stack and record it in poppedValues
                int v = sut.pop();
                poppedValues[v] = true;
            });
        }
        popThreadVector.join();
        EXPECT_TRUE(sut.isEmpty());

        for (int i=0; i<n; i++) {
            EXPECT_TRUE(poppedValues[i]);
        }

    }

}