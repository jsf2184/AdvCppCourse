//
// Created by Jeffrey on 5/21/2018.
//

#ifndef ADVCPPCOURSE_D_H
#define ADVCPPCOURSE_D_H


#include "C.h"

namespace jsf2184 {
    class NoX {

    public:
        NoX(int x) : _c(x) {}

        C getCValue() {
            return _c;
        }

        C &getCRef() {
            return _c;
        }

        int getX() {
            return _c.getX();
        }

    public:
        C _c;

    };

}
#endif //ADVCPPCOURSE_D_H
