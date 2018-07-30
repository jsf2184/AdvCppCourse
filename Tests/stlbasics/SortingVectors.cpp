//
// Created by Jeffrey on 5/23/2018.
//

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;
using  jsf2184::C;

namespace  XXX {

    void populate(vector<C> &v, int start, int count) {
        cout << endl << "beginning to populate vector" << endl;
        srand((unsigned) time(0));

        for (int i = 0; i < count; i++) {
            v.push_back(i + start);
        }

        // implementing a simple shuffle
        for (auto dest = v.begin(); dest < v.end(); dest++) {
            int r = rand() % count;
            iter_swap(dest, v.begin() + r);
        }

        cout << "done populating vector" << endl;
    }

    void print(const vector<C>::iterator &start, const vector<C>::iterator &finish) {
        cout << endl;
        for (auto it = start; it != finish; it++) {
            cout << *it << " ";
        }
        cout << endl;
    }


    void print(vector<C> &vec) {
        print(vec.begin(), vec.end());
    }

    bool cmp(const C &c1, const C &c2)  {
        return c1._x < c2._x;
    }

    TEST(SortingVector, SortPlay) {
        vector<C> vec;
        populate(vec, 10, 10);
        print(vec);

        // sort using class C's less than operator (the default)
        sort(vec.begin(), vec.end());
        print(vec);

        // sort supplying a lambda to do it the opposite way.
        sort(vec.begin(), vec.end(),[](C& c1, C &c2) { return c1.getX() > c2.getX();} );
        print(vec);

        // simply providing a function
        sort(vec.begin(), vec.end(), cmp );
        print(vec);

    }
}