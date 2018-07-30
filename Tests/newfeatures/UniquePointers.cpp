//
// Section 8 Lesson 68
//

#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include "../../XX.h"

using namespace std;

namespace jsf2184 {



    TEST(UPTR_TESTS, ptrToInt) {
        unique_ptr<int> ptr(new int(3));
        EXPECT_EQ(3, *ptr);
    }

    TEST(UPTR_TESTS, ptrToX) {
        cout << endl;
        unique_ptr<XX> ptr(new XX(3));
        EXPECT_EQ(3, ptr->getVal());
    }

    TEST(UPTR_TESTS, ptrToArray) {
        cout << endl;
        unique_ptr<XX[]> arr(new XX[3]);
        arr[0].setVal(0);
        arr[1].setVal(1);
        arr[2].setVal(2);

    }

    TEST(UPTR_TESTS, makeUniqueItem) {
        auto ptr = make_unique<XX>(3);
        EXPECT_EQ(3, ptr->getVal());
    }

    TEST(UPTR_TESTS, makeUniqueArray) {
        cout << endl;
        auto arr = make_unique<XX[]>(3);
        arr[0].setVal(0);
        arr[1].setVal(1);
        arr[2].setVal(2);
    }

    class XXOwner {
    public:
        XXOwner(int x) : _ptr(new XX(x)) {}

        int getVal() {
            return _ptr->getVal();
        }

    private:
        unique_ptr<XX> _ptr;
    };

    TEST(UPTR_TESTS, testXXOwner) {
        cout << endl;
        XXOwner xxOwner(99);
        EXPECT_EQ(99, xxOwner.getVal());
    }
    
    TEST(UPTR_TESTS, illegalHandoff) {
        unique_ptr<XX> ptr1 = make_unique<XX>(3);
        /* Copy constructor is deleted
        unique_ptr<XX> ptr2 = ptr1;
       */
    }

    TEST(UPTR_TESTS, rawPtrExposure) {
        unique_ptr<XX> ptr = make_unique<XX>(3);
        XX *raw = ptr.get();

        EXPECT_EQ(3, raw->getVal());

        // But it is still owned by the UniquePtr too!
        EXPECT_EQ(3, ptr->getVal());
        EXPECT_TRUE(ptr);
    }

    TEST(UPTR_TESTS, ptrMove) {
        unique_ptr<XX> ptr = make_unique<XX>(3);
        EXPECT_EQ(3, ptr->getVal());
        EXPECT_TRUE(ptr);

        unique_ptr<XX> ptr2 =  move(ptr);
        EXPECT_EQ(3, ptr2->getVal());
        EXPECT_TRUE(ptr2);
        EXPECT_FALSE(ptr);
    }

    TEST(UPTR_TESTS, ptrRelease) {
        unique_ptr<XX> ptr = make_unique<XX>(3);
        EXPECT_EQ(3, ptr->getVal());
        EXPECT_TRUE(ptr);

        XX *pXX = ptr.release();
        EXPECT_EQ(3, pXX->getVal());
        EXPECT_FALSE(ptr);
    }


}


