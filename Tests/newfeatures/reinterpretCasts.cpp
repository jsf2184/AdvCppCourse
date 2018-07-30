//
// Section 8 Lesson 65
//

#include <iostream>
#include <gtest/gtest.h>


using namespace std;

namespace jsf2184 {

    // two completely unrelated classes: X and Y
    class X {
    public:
        virtual int getX() {return 1;}
    };

    class Y {
    };

    TEST(RCASTS_TESTS, reinterpretCasts) {
        X x;
        Y *yR = reinterpret_cast<Y *>(&x);
        EXPECT_NE(nullptr, yR);

        Y *yC = (Y *)(&x);
        EXPECT_NE(nullptr, yC);

        /* A static cast won't succeed because the compiler knows it is a nonsensical cast.
        Y *yS = static_cast<Y *>(&x);
        */

        Y *yD = dynamic_cast<Y *>(&x);
        EXPECT_EQ(nullptr, yD);
    }

    struct S {
        int i;
        char c;
        bool b;
    };

    TEST(RCASTS_TESTS, reinterpretCastThatMakesSomeSense) {
        S s;
        s.i = 101;
        s.c = 'x';
        s.b = true;

        int *iPtr = reinterpret_cast<int *>(&s);
        EXPECT_EQ(101, *iPtr);
        iPtr++;
        char *cPtr = reinterpret_cast<char *>(iPtr);
        EXPECT_EQ('x', *cPtr);
        cPtr++;
        bool *bPtr = reinterpret_cast<bool *>(cPtr);
        EXPECT_EQ(true, *bPtr);

    }

}

