//
// Section 2 Lesson 4
//

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

class CanGoWrong {
public:
    // Learned: Constructors with one argument are now called conversion constructors.
    // They can make it possible to convert the single argument into an instance of the
    // class. If you don't want that to happen, use the 'explicit' keyword.
    //
    explicit CanGoWrong(bool throwIt) {
        if (throwIt) {
            throw logic_error("logicError");
        }
    }
};


namespace {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
    void verify(bool throwIt) {
        bool caught = false;
        try {
            CanGoWrong wrong(throwIt);
        }
        catch(logic_error &e) {
            const char *msg = e.what();
            cout << "Caught exception: " << msg << endl;
            caught = true;
        }

        EXPECT_EQ(throwIt, caught);

    }
#pragma clang diagnostic pop
    TEST(StandardExceptionsTest, ShouldCatch) {
        verify(true);
    }
    TEST(StandardExceptionsTest, ShouldNotCatch) {
        verify(false);
    }

}
