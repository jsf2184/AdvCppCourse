//
// Section 4 Lesson 18 - Maps With Custom Class As Key
//

#include <iostream>
#include <map>
#include <string>
#include <gtest/gtest.h>
#include "../Person.h"

using namespace std;

namespace {


    void add(map<Person, int> &aMap, const Person &person, int age) {
        aMap[person] = age;
    }

    void add(map<Person, int> &aMap, const Person &person) {
        add(aMap, person, person._age);
    }

    void populate(map<Person, int> &aMap) {
        add(aMap, Person("bob", 23));
        add(aMap, Person("zack",22));
        add(aMap, Person("alex",24));
        add(aMap, Person("jeff",61));

        cout << "about to re-add bob " << endl;
        cout.flush();
        add(aMap, Person("bob", 23), 33);


    }


    void print(const map<Person, int> &aMap) {
        cout << endl << "printing map of size: " << aMap.size() << endl;
        for (auto it = aMap.cbegin(); it != aMap.cend(); it++) {
            cout << it->first.toString() << "->"  << it->second << endl;
        }
    }

    TEST(StlCustomValueMap, ItereateTest) {
        cout << endl;
        map<Person, int> people;
        populate(people);
        print(people);
    }


}