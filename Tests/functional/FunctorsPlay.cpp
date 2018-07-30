//
// Section 7 Lesson 38 - Function Pointers
//


#include <iostream>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;


namespace  jsf2184 {

    template<class T> class BaseFunctor {
    public:
        virtual bool operator()(const T &val) = 0;
    };

    template<class T> class MyFunctor : public BaseFunctor<T> {
    public:
        MyFunctor(const T &value) : _value(value) {}

        // we overload operator () so that using the Functor looks simply like calling a function.
        bool operator()(const string &val) {
            return  val == _value;
        }

    private:
        T _value;
    };

    TEST(FunctorsTests, testFunctorCall) {
        MyFunctor<string> mf("abc");

        // Since MyFunctor overloads '()' we can call it like a function call.
        ASSERT_TRUE(mf("abc"));
        ASSERT_FALSE(mf("def"));
    }


    template<class T>
    bool callFunctor(const T &val, BaseFunctor<T> &functor) {
        return functor(val);
    }

    TEST(FunctorsTests, testIndirectFunctorCall) {
        MyFunctor<string> mf("abc");

        // Since MyFunctor overloads '()' we can call it like a function call.
        ASSERT_TRUE(callFunctor<string>("abc", mf));
        ASSERT_FALSE(callFunctor<string>("def", mf));
    }

}
