#include <iostream>
#include <gtest/gtest.h>
#include <limits>
#include <climits>

using namespace std;


namespace  jsf2184 {

    TEST(ARRAY_PLAY, oneDim) {
        cout << endl;
        const char *cptr = "abcdefghijkl";
        cout << "cptr size = " << sizeof(cptr) << endl;
        char charArray[7] = "defghi";
        cout << "charArray size = " << sizeof(charArray) << endl;

        // these are legal
        char carray1[10];
        char carray2[] = {'a', 'b', 'c'};
        char carray3[] = "abc";


        // These are all illegal
//        char badArray1[];
//        char badArray2[2] = "def";

    }
}
