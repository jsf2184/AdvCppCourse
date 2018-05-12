//
// Section 2 Lesson 3
//
#include <iostream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

namespace  {

    enum ThrowType {
        ThrowCharPtr,
        ThrowStr,
        ThrowInt,
        ThrowFloat,
        ThrowUnknown,
        ThrowNone
    };

    void mightGoWrong(ThrowType throwType) {

        switch(throwType) {
            case ThrowCharPtr:
                throw "char ptr value"; // NOLINT
            case ThrowStr:
                throw string("string value"); // NOLINT
            case ThrowInt:
                throw 3; // NOLINT
            case ThrowFloat:
                throw 3.6; // NOLINT
            case ThrowNone:
                break;
            case ThrowUnknown:
                break;
        }
    }

    void usesMightGoWrong(ThrowType throwType) {
        mightGoWrong(throwType);
    }

    void validate(ThrowType throwType, ThrowType expected) {
        ThrowType  caughtType = ThrowNone;

        try {
            usesMightGoWrong(throwType);
        }
        catch(int e) {
            caughtType = ThrowInt;
        }
        catch( const char  * e) {
            caughtType = ThrowCharPtr;
        }
        catch( string &e) {
            caughtType = ThrowStr;
        }
        catch (...) {  // I added this to illustrate it catches anything
           caughtType = ThrowUnknown;
        }
        EXPECT_EQ(expected, caughtType);
    }

    TEST(BasicExceptionsTest, TestThrowCharPtr) {
        validate(ThrowCharPtr, ThrowCharPtr);
    }
    TEST(BasicExceptionsTest, TestThrowStr) {
        validate(ThrowStr, ThrowStr);
    }
    TEST(BasicExceptionsTest, TestThrowInt) {
        validate(ThrowInt, ThrowInt);
    }
    TEST(BasicExceptionsTest, TestThrowNone) {
        validate(ThrowNone, ThrowNone);
    }
    TEST(BasicExceptionsTest, TestThrowUnknown) {
        validate(ThrowFloat, ThrowUnknown);
    }
}

