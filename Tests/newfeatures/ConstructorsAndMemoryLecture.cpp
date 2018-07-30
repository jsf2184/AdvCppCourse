//
// Section 8 Lesson 57 - ConstructorAndMemory
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>

using namespace std;


namespace  jsf2184 {

    int *allocAndInit(int val, int size) {
        int *res = new int[size] {};
        return res;
    }
    
    TEST(ConstructAndMemoryTests, validateInit) {
        int *const data = allocAndInit(1, 10);
        for (int i=0; i< 10; i++) {
            EXPECT_EQ(0, data[i]);
        }
    }
}