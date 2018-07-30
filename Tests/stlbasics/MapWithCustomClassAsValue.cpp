//
// Section 4 Lesson 17 - Maps With Custom Class As Value
//

#include <iostream>
#include <map>
#include <string>
#include <gtest/gtest.h>

using namespace std;

namespace {

    class Person {
    private:
        string _name;
        int _age;

    public:

        Person() :
                _name(""), _age(0)
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

        void  print(const string &label) const {
            cout << label << ": " <<  _name << ": " << _age << endl;
        }
    };

    void populate(map<int, Person> &aMap) {
        aMap[52] = Person("bob", 23);
        cout << "calling make_pair" << endl;
        auto alexPair = make_pair(53, Person("alex", 25));
        cout << "back from make_pair, about to insert" << endl;
        aMap.insert(alexPair);
        cout << "done inserting alexPair" << endl;
        aMap[54] = Person("zack", 22);
        aMap[55] = Person("peter", 100);
        aMap[56] = Person("jim", 24);
    }

    void print(const map<int, Person> &aMap) {
        cout << endl << "printing map of size: " << aMap.size() << endl;
        for (auto it = aMap.cbegin(); it != aMap.cend(); it++) {
            cout << it->first << "->" ;
            it->second.print("");
        }
    }

    TEST(StlCustomValueMap, ItereateTest) {
        cout << endl;
        map<int, Person> people;
        populate(people);
        print(people);
    }
    TEST(StlCustomValueMap, GetTest) {
        cout << endl;
        map<int, Person> people;
        populate(people);
        Person zack =  people[54];
        zack.print("Zack");
        Person noone = people[0];
        noone.print("noone");
    }


}