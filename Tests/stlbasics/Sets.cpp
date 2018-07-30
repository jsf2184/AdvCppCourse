//
// Created by Jeffrey on 5/18/2018.
//

#include <iostream>
#include <map>
#include <string>
#include <gtest/gtest.h>
#include "../../C.h"
#include "../../D.h"

using namespace std;
using  jsf2184::C;

namespace {
    void populate(set<jsf2184::C> &cSet ) {
        cout << "populate() entry" << endl;
        for (int i=0; i <= 20; i+=2) {
            cout << "iteration for i = " << i << endl;
            cSet.insert(jsf2184::C(i));
        }
        cout << "populate() return" << endl;
    }
    void print(set<jsf2184::C> const &cSet ) {
        cout << endl;
        for (auto it = cSet.cbegin(); it != cSet.end(); it++) {
            cout << *it << endl;
        }
    }

    void populate(set<int> &mySet ) {
        cout << "populate() entry" << endl;
        for (int i=0; i <= 20; i+=2) {
            mySet.insert(i);
        }
        cout << "populate() return" << endl;
    }
    void print(set<int> const &cSet ) {
        cout << endl;
        for (auto it = cSet.cbegin(); it != cSet.end(); it++) {
            cout << *it << endl;
        }
    }

    void checkExistence(set<int> const &cSet, int x ) {
        if (cSet.count(x)) {
            cout << "found: " << x << endl;
        } else {
            cout << "did not find: " << x << endl;
        }
    }

    TEST(StlSets, CSetPlay) {
        set<jsf2184::C> cSet;
        populate(cSet);
        print(cSet);

        // only odds in the set so shouldn't be found.
        EXPECT_EQ(cSet.end(), cSet.find(3));

        // it should find 4.
        EXPECT_EQ(C(4), *cSet.find(4));


//        std::remove_if(cSet.begin(), cSet.end(), [] (const jsf2184::C &c) { return c.getX() %4 == 0;});


    }

    TEST(StlSets, IntSetPlay) {
        set<int> mySet;
        populate(mySet);
        print(mySet);

        // only odds in the set so shouldn't be found.
        EXPECT_EQ(mySet.end(), mySet.find(3));

        // it should find 4.
        EXPECT_EQ(C(4), *mySet.find(4));

        checkExistence(mySet, 4);
        checkExistence(mySet, 3);



//        remove_if(mySet.begin(), mySet.end(), [] (int i) { return i %4 == 0;});
        for (set<int>::iterator it = mySet.begin(); it != mySet.end(); ) {
            if (*it % 4 != 0) {
                it = mySet.erase(it);
            } else {
                it++;
            }
        }
        cout << "pruned set" << endl;
        print(mySet);
        cout << "pruned set using for_each" << endl;
        for_each(mySet.begin(), mySet.end(), [] (int i) {cout << i << " ";}) ;
        cout << endl;

    }

}
