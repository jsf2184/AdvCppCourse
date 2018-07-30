//
// My own play
// Also, gets in to lvalue and rvalues covered in Section 8,
// Lectures: 58, 59, 60
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>

using namespace std;


namespace  jsf2184 {
    TEST(PrefixPostfix, preIncTest) {
        int x = 10;
        int y = x++; // assign to y, then increment x
        EXPECT_EQ(10, y);
        EXPECT_EQ(11, x);
    }

    TEST(PrefixPostfix, postIncTest) {
        int x = 10;
        int y = ++x;     // increment x, then assign to y.
        EXPECT_EQ(11, x);
        EXPECT_EQ(11, y);
    }

    TEST(PrefixPostfix, preIncTestAddrTest) {
        int x = 10;
        int *y = &++x;   // increment x, then set y to the address of x.
        EXPECT_EQ(11, x);
        EXPECT_EQ(11, *y);
        EXPECT_EQ(y, &x);
    }

    TEST(PrefixPostfix, postIncTestAddrTest) {
        int x = 10;


        // The following won't compile. It would like to assign to y a pointer
        // an integer that has not yet been incremented. But, that value is no
        // longer sitting in the 'x' variable. It is in some temporary location
        // but you can't take an address of a a temporary (i.e. RVALUE) so it won't
        // compile.
        //

        /*                 THE FOLLOWING WONT COMPILE
        int *y = &x++;
        */
    }

}
