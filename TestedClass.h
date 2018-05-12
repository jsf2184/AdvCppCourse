//
// Created by Jeffrey on 5/11/2018.
//

#ifndef SETTINGUPGOOGLETEST_TESTCLASS_H
#define SETTINGUPGOOGLETEST_TESTCLASS_H


class TestedClass {
public:
    TestedClass(int x);

    int getX() const;

private:
    int _x;

};


#endif //SETTINGUPGOOGLETEST_TESTCLASS_H
