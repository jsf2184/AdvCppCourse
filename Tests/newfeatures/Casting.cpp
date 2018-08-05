//
// Section 8 Lesson 64
//

#include <iostream>
#include <gtest/gtest.h>


using namespace std;

namespace jsf2184 {


    TEST(CASTING_TESTS, simpleFloatToIntCasts) {
        cout << endl;
        double  d = 3.17;

        int i =  (int) d ;
        EXPECT_EQ(i, 3);

        i = int(d);
        EXPECT_EQ(i, 3);

        i = static_cast<int>(d);
        EXPECT_EQ(i, 3);

        /* compiler error since dynamic casts work only on pointers or references
        i = dynamic_cast<int>(d);
        */

        /* compiler error
        i = reinterpret_cast<int>(d);
        */
    }

    TEST(CASTING_TESTS, primitivePointerCasts) {
        double  d = 3.17;

        int *iPtr;
        // blatantly wrong cast is allowed
        iPtr =  (int *) &d ;

        /* blatantly wrong cast is not allowed
        iPtr = static_cast<int *>(&d);
        */

        /* dynamic casts work on pointers and refs to classes not primitive types
        iPtr = dynamic_cast<int *>(&d);
        */
        // not a good idea, but leeway seems to be allowed.
        iPtr = reinterpret_cast<int *>(&d);

    }


    class B {
    public:
        virtual string getName() {
            return "B";
        }
    };

    class NoX : public B {
    public:
        virtual string getName() {
            return "D";
        }
    };

    TEST(CASTING_TESTS, upCasts) {
        NoX d;
        B *bptr;

        // casting is not even required.
        bptr = &d;
        EXPECT_EQ("D", bptr->getName());

        // fine
        bptr = static_cast<B *>(&d);
        EXPECT_EQ("D", bptr->getName());

        // fine
        bptr = dynamic_cast<B *>(&d);
        EXPECT_EQ("D", bptr->getName());

        // fine
        bptr = reinterpret_cast<B *>(&d);
        EXPECT_EQ("D", bptr->getName());

    }

    TEST(CASTING_TESTS, goodDownCasts) {
        NoX d;
        B *bptr = &d;
        NoX *dptr;

        // simple cast works fine.
        dptr = (NoX *) bptr;
        EXPECT_EQ("D", dptr->getName());

        // works fine
        dptr = static_cast<NoX *>(bptr);
        EXPECT_EQ("D", dptr->getName());

        // works fine
        dptr = dynamic_cast<NoX *>(bptr);
        EXPECT_EQ("D", dptr->getName());

        // works fine
        dptr = reinterpret_cast<NoX *>(bptr);
        EXPECT_EQ("D", dptr->getName());
    }

    TEST(CASTING_TESTS, badDownCasts) {
        B b;
        B *bptr = &b;
        NoX *dptr;

        // simple invalid cast is allowed
        dptr = (NoX *) bptr;

        // invalid static cast is allowed
        dptr = static_cast<NoX *>(bptr);

        // dynamic cast knows that this is not good.
        dptr = dynamic_cast<NoX *>(bptr);
        EXPECT_EQ(nullptr, dptr);

        // invalid reinterpret_cast is allowed
        dptr = reinterpret_cast<NoX *>(bptr);
    }

    // X and Y are two unrelated classes.
    class X {
    public:
        virtual int getX() {return 0;}
    };
    class Y {};

    TEST(CASTING_TESTS, badUnrelatedCasts) {
        X x;
        X *xptr = &x;
        Y *yptr;

        // simple invalid cast is allowed
        yptr = (Y *) xptr;

        /* unrelated invalid static cast is allowed
        yptr = static_cast<Y *>(xptr);
        */

        // dynamic cast knows that this is not good.
        yptr = dynamic_cast<Y *>(xptr);
        EXPECT_EQ(nullptr, yptr);

        // invalid reinterpret_cast is allowed
        yptr = reinterpret_cast<Y *>(xptr);


    }


}
