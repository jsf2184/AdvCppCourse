//
// Section 8 Lesson 59 - LValue References
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>
#include "../../C.h"

using namespace std;


namespace  jsf2184 {
    TEST(LValueRefTests, AddLvRefToCollection) {
        cout << endl;
        vector<C> vec;
        vec.push_back(C(100));
        cout << endl <<  vec[0] << endl;
    }

    TEST(LValueRefTests, AssignLvalToRef) {
        cout << endl;
        C c(3);
        C &cRef = c;
        cout << endl <<  cRef << endl;
    }

    TEST(LValueRefTests, AssignRvalToRef) {
        /* Can't assign a normal ref to an rvalue - won't compile
        C &cRef = C(4);
        */
    }

    TEST(LValueRefTests, AssignRvalToConstRef) {
        cout << endl;
        // However, an rvalue can be assigned to a const ref.
        const C &cref = C(4);
        cout << endl <<  cref << endl;

    }

}


