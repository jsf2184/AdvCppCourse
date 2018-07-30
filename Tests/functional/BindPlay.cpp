//
// Section 8 Lesson 67
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>

using namespace std;
using namespace placeholders;

namespace jsf2184 {

    int add(int x, int y) {
        return x+y;
    }
    TEST(BIND_TESTS, simpleCFunc) {
        auto invoke0 = bind(add, 3, 4);
        EXPECT_EQ(7, invoke0());
        auto invoke1 = bind(add, 3, _1);
        EXPECT_EQ(13, invoke1(10));
        auto invoke2 = bind(add, _1, _2);
        EXPECT_EQ(27, invoke2(14, 13));
    }

    int callIt(function<int(int)> f, int x) {
        int res = f(x);
        return res;
    }

    class Adder {
    public:
        Adder(int val) : _val(val) {}

        int addIt(int x) {
            return _val + x;
        }
    private:
        int _val;
    };

    TEST(BIND_TESTS, methodBind) {
        Adder adder(3);
        auto boundCall = bind(&Adder::addIt, adder, _1);
        EXPECT_EQ(23, boundCall(20));

        int res = callIt(boundCall, 9);
        EXPECT_EQ(12, res);
    }

}

