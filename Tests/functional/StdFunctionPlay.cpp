//
// Section 8 Lesson 53 - StdFunctions
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>

using namespace std;


namespace  jsf2184 {

    bool testEven(int v) {
        return v % 2 == 0;
    }

    class ModChecker {
    public:
        ModChecker(int mod) : _mod(mod) {}
        bool operator()(int val) const {
            return val % _mod == 0;}
    private:
        int _mod;
    };

    TEST(FunctionPlayTests, count_if_lambda_test) {
        vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const auto res = count_if(vec.begin(), vec.end(), [](int i) { return i % 2 == 0;});
        EXPECT_EQ(5, res);
    }

    TEST(FunctionPlayTests, count_if_fptr_test) {
        vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        const auto res = count_if(vec.begin(), vec.end(), &testEven);
        EXPECT_EQ(5, res);
    }

    TEST(FunctionPlayTests, count_if_functor_test) {
        vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        ModChecker modChecker(2);
        const auto res = count_if(vec.begin(), vec.end(), modChecker);
        EXPECT_EQ(5, res);
    }

    class DivChecker {
    public:
        DivChecker(int divisor) : _divisor(divisor) {}
        bool isDivisible(int num) {
            return num % _divisor == 0;
        }
    private:
        int _divisor;
    };


}