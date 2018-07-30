//
// Section 8 Lesson 48 - ObjectInitialization And Default Methods
//


#include <iostream>
#include <gtest/gtest.h>

using namespace std;


namespace  jsf2184 {

    class X {
    public:
        X(int x) : _x(x) {}

        X() = default;

        // suppose you don't want a copy constructor
        X(const X &other)  = delete;

        friend ostream &operator << (ostream &os, const X &rec) {
            os << "_x = " << rec._x << " _y = " << rec._y;
        }

//        bool operator ==(const X &other) = default;
        X &operator =(const X &other) = default;

    private:
        // provide default values
        int _x = 3;
        int _y {4};
    };

    TEST(ObjectInitTests, constructors) {
        X x1;
        cout << x1 << endl;

        X x2(100);
        cout << x2 << endl;
    }

}