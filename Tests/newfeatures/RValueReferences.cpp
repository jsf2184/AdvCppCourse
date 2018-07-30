//
// Section 8 Lesson 60 - RValue References
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>
#include "../../C.h"

using namespace std;


namespace  jsf2184 {


    TEST(RValueRefTests, AssignRvalToRvalRef) {
        C &&cRef = C(4);
        cRef.setX(3);
        cout << endl <<  cRef << endl;
        EXPECT_EQ(3, cRef.getX());
    }

    TEST(RValueRefTests, AssignFuncReturnToRvalRef) {
        C &&cRef = C::createC(9);
        cout << endl <<  cRef << endl;
        EXPECT_EQ(9, cRef.getX());
        cRef.setX(10);
        EXPECT_EQ(10, cRef.getX());
    }

    TEST(RValueRefTests, AssignPostfixIncToRvalRef) {
        int x = 10;
        int &&xRef = x++;
        EXPECT_EQ(11, x);
        EXPECT_EQ(10, xRef);
    }


    TEST(RValueRefTests, AssignLvalToRvalRef) {
        cout << endl;
        const C c = C(4);
        /* Compiler error trying to assign an Lval to an RVal ref.
        C&& cRef = c;
         */

    }

}


