//
// Section 8 Lesson 66
// there are other examples of perfect forwarding
// in 'MoveConstructorTestsWithCustomStrClass.cpp'
//

#include <iostream>
#include <gtest/gtest.h>
using namespace std;

namespace jsf2184 {

    class B {
    public:
        virtual string getName() {
            return "B";
        }
    };

    B createB() {
        B b;
        return b;
    }

    TEST(PFORWARDING_TESTS, AssignLvalToRvalRef) {
        B b;
        /* Can't assign lValue to RVal ref
        B &&bRef = b;
         */
    }

    TEST(PFORWARDING_TESTS, AssignLvalToRvalRefAuto) {
        B b;
        /* Can assign lValue to RVal ref auto since it won't really behave like an RVal ref */
        auto &&bRef = b;
    }
    TEST(PFORWARDING_TESTS, AssignLvalToFuncReturn) {
        /* Can assign lValue to RVal ref auto since it won't really behave like an RVal ref */
        auto &&bRef = createB();
    }

    string check(B &b) {
        return "lval";
    }

    string check(B &&b) {
        return "rval";
    }


    template <typename T>
    string callCheck(T &&arg) {
        string res = check(forward<T>(arg));
        return res;
    }

//    template <typename T>
//    void callCheck(T &arg) {
//        cout << "callCheck with lval ref" << endl;
//        check(arg);
//    }

    TEST(PFORWARDING_TESTS, rvalueForwarding) {
        cout << endl;
        string res = callCheck(createB());
        EXPECT_EQ("rval", res);
    }

    TEST(PFORWARDING_TESTS, lvalueForwarding) {
        cout << endl;
        B b;
        string res = callCheck(b);
        EXPECT_EQ("lval", res);
    }

}