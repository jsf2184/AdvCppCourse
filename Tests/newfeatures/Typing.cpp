//
// Section 8 Lesson 39- DeclType and TypeID
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <typeinfo>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;
using  jsf2184::C;

namespace {

    TEST(TypingTests, primitives) {
        int anInt;
        double aDouble;
        string aString;
        C myC(3);

        int anIntArray[11];
        vector<string> svector;
        vector<int> ivector;

        cout << "anInt type is " << typeid(anInt).name() << endl;
        cout << "aDouble type is " << typeid(aDouble).name() << endl;
        cout << "aString type is " << typeid(aString).name() << endl;
        cout << "anIntArray type is " << typeid(anIntArray).name() << endl;

        cout << "myC type is " << typeid(myC).name() << endl;
        // declare a new local whose type is the same as 'myC'
        decltype(myC) yourC(29);
        cout << "yourC type is " << typeid(yourC).name() << endl;

        cout << "svector type is " << typeid(svector).name() << endl;
        cout << "ivector type is " << typeid(ivector).name() << endl;

        auto intAuto = 7;
        cout << "intAuto type is " << typeid(intAuto).name() << endl;
        auto autoCharPtr = "abc";
        cout << "autoCharPtr type is " << typeid(autoCharPtr).name() << endl;

        const char  *regCharPtr = "abc";
        cout << "regCharPtr type is " << typeid(regCharPtr).name() << endl;

    }

    double  getDoubleValue() {
        return 10;
    }

    // this is called a trailing type, and it means that the type of callGetValue()
    // is the same as the declaredType of getDoubleValue().
    auto callGetDoubleValue() -> decltype(getDoubleValue()) {
        return getDoubleValue();
    }
}
