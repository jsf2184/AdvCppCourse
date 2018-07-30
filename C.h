//
// Created by Jeffrey on 5/18/2018.
//

#ifndef ADVCPPCOURSE_C_H
#define ADVCPPCOURSE_C_H


#include <iostream>
#include <ostream>

using namespace std;

namespace jsf2184 {class C;}

namespace XXX {
    // forward declare the function in XXX namespace that we are going to
    // grant 'friend' rights to.
    //
    bool cmp(const jsf2184::C &c1, const jsf2184::C &c2);
}

namespace  jsf2184 {
    class C {
    public:

        C() : C(1) {}

        C(int x) : _x(x) {
            if (!_silent) {
                cout << endl << "'C' NORMAL constructor w/ _x = "  << _x << endl;
            }

        }

        // rule of 3: if you provide one, provide all of
        //  assignment operator
        //  copy constructor
        //  destructor
        //
        C(const C &c) {
            // could alternatively do *this = other;
            _x = c._x;
            if (!_silent) {
                cout << endl << "'C' Copy constructor w/ _x = "  << _x << endl;
            }
        }

        C(const C &&c) {
            _x = c._x;
            if (!_silent) {
                cout << endl << "'C' MoveSemantics constructor w/ _x = "  << _x << endl;
            }
        }

        // override default implementation of operator = which does a shallow copy
        C &operator=(const C &c) {
            if (!_silent) {
                cout << endl << "'C' assignment operator" << endl;
            }
            _x = c._x;
            return *this;
        }

        // override default implementation of operator = which does a shallow copy
        C &operator=(const C &&c) {
            if (!_silent) {
                cout << endl << "'C' move-semantics assignment operator" << endl;
            }
            _x = c._x;
            return *this;
        }


        virtual ~C() {
            if (!_silent) {
                cout << endl << "'C' destructor w/_x =" << _x << endl;
            }
        }

        int getX() const {
            return _x;
        }

        void setX(int x) {
            _x = x;
        }

        bool operator==(const C &rhs) const {
            return _x == rhs._x;
        }

        bool operator< (const C &rhs) const {
            return _x < rhs._x;
        }

        bool operator!=(const C &rhs) const {
            return !(rhs == *this);
        }


        // operator << has 2 args, the ostream and the object being printed.
        // note that normally we'd just implement it here (inline) but to show how we do it
        // in a .cpp file, see .cpp.
        //
        friend std::ostream &operator<<(std::ostream &os, const C &c); /* {
            os << "_x: " << c._x;
            return os;
        }
*/
        friend bool XXX::cmp(const jsf2184::C &c1, const jsf2184::C &c2);

        static C createC(int x) {
            return C(x);
        }

    private:
        int _x;
        static bool _silent;


    };

}
#endif //ADVCPPCOURSE_C_H
