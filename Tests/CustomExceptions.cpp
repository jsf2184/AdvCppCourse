//
// Section 2 Lesson 5
//

#include <exception>
#include <gtest/gtest.h>

using namespace std;
namespace {

    class MyException: public exception {
    public:
        // Learned: the noexcept tag gives some indication that the method
        // won't/shouldn't throw. Probably a good idea since this call is often
        // made in an exception handler.
        //
        // Learned: use the keyword override when overridng a virtual method.
        //
        const char *what() const noexcept override {
            return "MyException description";
        }

    };

    class Thrower {
    public:
        void goesWrong() {
            throw MyException();
        }
    };

    TEST(CustomExceptionTest, ShouldCatch) {
        Thrower thrower;
        bool caught = false;
        try {
            thrower.goesWrong();
        } catch (MyException &e) {
            caught = true;
            cout << "caught custom exception: " << e.what() << endl;
        }
        EXPECT_TRUE(caught);
    }

}