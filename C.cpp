//
// Created by Jeffrey on 5/22/2018.
//
#include "C.h"

using jsf2184::C;

bool C::_silent = false;

namespace  jsf2184 {
    std::ostream &operator<<(std::ostream &os, const C &c) {
        os << "_x: " << c._x;
        return os;
    }

}
