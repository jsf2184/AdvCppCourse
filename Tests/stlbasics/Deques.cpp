//
// Created by Jeffrey on 5/25/2018.
//

#include <iostream>
#include <deque>  //Double Ended Queue
#include <string>
#include <gtest/gtest.h>
#include "../../C.h"


using namespace std;

namespace jsf2184 {
    void populateBack(deque<C> &aDeque, int start, int count) {
        for (int i=start; i<start+count; i++) {
            aDeque.push_back(i);
        }
    }

    void populateFront(deque<C> &aDeque, int start, int count) {
        for (int i=start; i<start+count; i++) {
            aDeque.push_front(i);
        }
    }

    void print(deque<C> &aDeque) {
        for (auto it = aDeque.begin(); it < aDeque.end(); it++) {
            cout << *it << " ";
        }
    }

    TEST(DequeTests, popAndPrint) {
        deque<C> aDeque;
        populateBack(aDeque, 10, 10);
        print(aDeque);
        cout << endl;
        populateFront(aDeque, 0, 10);
        print(aDeque);

    }
}