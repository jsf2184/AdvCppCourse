//
// Created by Jeffrey on 5/26/2018.
//

#ifndef ADVCPPCOURSE_COMPLEXNUM_H
#define ADVCPPCOURSE_COMPLEXNUM_H

#include <ostream>
using namespace std;

namespace jsf2184 {



    class ComplexNum {

    public:
        ComplexNum() : ComplexNum(0, 0) {};
        ComplexNum(double real, double imaginary) : _real(real), _imaginary(imaginary) {};
        ComplexNum(double real) : ComplexNum(real, 0.0) {};
//        ComplexNum(const ComplexNum &other) {
//            *this = other;
//        }
        ~ComplexNum(){}


        ComplexNum & operator=(const ComplexNum &other) {
            _real = other._real;
            _imaginary = other._imaginary;
            return *this;
        }

        bool operator==(const ComplexNum &other) {
            return _real == other._real && _imaginary == other._imaginary;
        }

        bool operator!=(const ComplexNum &other) {
            return !operator==(other);
        }

        friend ostream &operator<<(ostream &os, const ComplexNum &complexNum) {
            os << "(" << complexNum._real << ", " << complexNum._imaginary << ")";
            return os;
        }

//        friend ComplexNum operator+(const ComplexNum &a, const ComplexNum &b) {
//            return ComplexNum(a._real + b._real, a._imaginary + b._imaginary);
//        }

        ComplexNum operator+(const ComplexNum &other) const {
            return ComplexNum(_real + other._real, _imaginary + other._imaginary);
        }

        friend ComplexNum operator+(double d, const ComplexNum &c)  {
            return ComplexNum(c._real + d, c._imaginary);
        }


    private:
        double _real;
        double _imaginary;
    };

}


#endif //ADVCPPCOURSE_COMPLEXNUM_H
