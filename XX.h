//
// Created by Jeffrey on 7/30/2018.
//

#ifndef ADVCPPCOURSE_XX_H
#define ADVCPPCOURSE_XX_H

#include <iostream>
using namespace std;

class XX {
public:

    XX() : XX(0) {}

    XX(int val) : _val(val) {
        cout << "The XX Constructor with _val = "
             << _val
             << endl;
    }

    virtual ~XX() {
        cout << "The XX Destructor with _val = " << _val << endl;
    }

    int getVal() const {
        return _val;
    }

    void setVal(int val) {
        _val = val;
    }

private:
    int _val;
};

#endif //ADVCPPCOURSE_XX_H
