//
// Created by Jeffrey on 5/18/2018.
//


#include <iostream>
#include <gtest/gtest.h>
#include "../../C.h"
#include "../../D.h"

using namespace std;

namespace  jsf2184 {
    C returnCVal() {
        cout << endl <<  "returnCval(): entered" << endl;
        C res(3);
        cout << endl <<  "returnCval(): returning" << endl;
        return res;
    }

    C &returnCRef() {
        cout << endl <<  "returnCRef(): entered" << endl;
        C res(3);
        cout << endl <<  "returnCRef(): returning" << endl;
        return res;
    }


    void acceptCRef(C &c) {
        cout << "acceptCRef(): called" << c << endl;
    }

    void acceptConstCref(const C &c)  {
        cout << "acceptConstCRef(): called" << c << endl;
    }

    void acceptRvalCref(const C &&c)  {
        cout << "acceptConstCRef(): called" << c << endl;
    }


    void acceptCVal(C c) {
        cout << "acceptCVal(): called" << c << endl;
    }


    int return_int() {
        int a {123};
        return a; // Returning a reference to something on the stack!
    }

    TEST(RefPlayTests, testRefPassing) {
        C c(3);
        acceptCRef(c);

        /* not allowed since returnCVal() returns an rValue
        acceptCRef(returnCVal()); */

        acceptConstCref(returnCVal());

        acceptRvalCref(returnCVal());


    }

    TEST(RefPlayTests, testDanglingRefOkForConstRef) {
        cout << endl;
        const int &int_ref(return_int());
//        std::cout << "Some stack overwriting intermediate print" << std::endl;
        std::cout << int_ref << std::endl;
    }


    TEST(RefPlayTests, testReturnCValAssignedToRef) {
//         C &cref = returnCVal(); // compiler doesn't allow
    }

    TEST(RefPlayTests, testDreturnsCValAssignedToRef) {
        NoX d(3);


//      C &cref = d.getCValue(); // compiler doesn't allow. Left side needs to be lvalue.
        C &cRef = d.getCRef();
        cout << endl << "call d.getCValue() first" << endl;
        // const refs to temporary objects are permitted:
        // see: https://blog.galowicz.de/2016/03/23/const_reference_to_temporary_object/
        //
        const C &refToCVal = d.getCValue();

        cout << endl << "back from d.getCValue() first" << endl;
        C otherC = d.getCValue();
        cout << endl << "back from d.getCValue() second" << endl;

//      cValue.setX(4);   // not allowed since const.
        EXPECT_EQ(3, cRef.getX());

        cRef.setX(4);

        auto cValue = d.getCValue();
        cout << "cvalue.getX() = "
             << cValue.getX()
             << ", cRef.getX() = "
             << cRef.getX()
             << endl;

//        EXPECT_EQ(3, refToCVal.getX());

        EXPECT_EQ(4, d.getX());

        cout << "done with test" << endl;

    }

    TEST(RefPlayTests, StringRefAssign) {
        const string &a = string("abc");
    }
    TEST(RefPlayTests, testReturnCValAssignedToVal) {
        cout << endl;
        C c = returnCVal();
        cout << c << endl;
    }

    TEST(RefPlayTests, testReturnCRefAssignedToVal) {
        cout << endl;
        C c = returnCRef();
        cout << c << endl;
    }

    TEST(RefPlayTests, testReturnCRefAssignedToRef) {
        cout << endl;
        C &c = returnCRef();
        cout << c << endl;
    }

    TEST(RefPlayTests, testOutputOverload) {
        C c(10);
        cout << endl << c << endl;
    }


}