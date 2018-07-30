//
// Section 2 Lesson 6
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

    enum ThrowType {
        Mine,
        Base,
        None
    };
    class Thrower {
    public:
        void goesWrong(ThrowType throwType) {
            switch(throwType) {
                case Mine:
                    throw MyException();
                case Base:
                    throw exception();
                case None:
                    break;
            }
        }
    };

    void validate(ThrowType throwType) {
        Thrower thrower;
        ThrowType  caughtType = ThrowType::None;
        try {
            thrower.goesWrong(throwType);
        } catch (MyException &e) {
            caughtType = Mine;
        } catch (exception &e) {
            caughtType = Base;
        }
        EXPECT_EQ(throwType, caughtType);
    }
    TEST(CustomExceptionTest, ShouldCatchMine) {
        validate(Mine);
    }
    TEST(CustomExceptionTest, ShouldCatchBase) {
        validate(Base);
    }
    TEST(CustomExceptionTest, ShouldCatchNone) {
        validate(None);
    }

}