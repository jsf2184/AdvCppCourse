//
// Created by Jeffrey on 5/25/2018.
//

#ifndef ADVCPPCOURSE_PERSON_H
#define ADVCPPCOURSE_PERSON_H

#include <string>

using namespace std;

class Person {

public:

    string _name;
    int _age;

    Person() :
            _name(), _age(0)
    {
        cout << "Default Person constructor running" << endl;
    }

    Person(string name, int age) :
            _name(name), _age(age) {

    }

    Person(const Person &other)
            : _name(other._name),
              _age(other._age)
    {
        other.print("Copy constructor running");
    }

    Person &operator = (const Person &other) {
        _name = other._name;
        _age = other._age;
        print("assigment operator running");

    }

    string toString() const {
        stringstream ss;
        ss << "name = " << _name << ", age = " << _age << ends;
        auto res = ss.str();
        return res;
    }
    void  print(const string &label) const {
        cout << label << ": " << toString() << endl;
    }

    bool operator < (const Person &other) const  {

        cout << "Comparing me [" << toString() << "] to other [" << toString() << "]" << endl;
        bool res;
        if (_name == other._name) {
            res = _age < other._age;
        } else {
            res = _name < other._name;
        }
        return res;
    }

};


#endif //ADVCPPCOURSE_PERSON_H
