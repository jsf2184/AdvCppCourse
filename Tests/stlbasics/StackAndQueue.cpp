//
// Section 4 Lesson 21 - Lists
//

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;
using  jsf2184::C;

namespace {

    void populate(stack<C> &res, int start, int count) {
        cout << endl << "beginning to populate stack" << endl;
        for (int i= 0; i<count; i++ ) {
            res.push(C(start+i));
        }
        cout << "done populating stack" << endl;
    }

    void populate(queue<C> &res, int start, int count) {
        cout << endl << "beginning to populate queue" << endl;
        for (int i= 0; i<count; i++ ) {
            res.push(C(start+i));
        }
        cout << "done populating queue" << endl;
    }

    // note no iterating thru a stack.

    TEST(StackQueue, stackPlay) {
        stack<C> myStack;
        populate(myStack, 0, 10);
        cout << endl;
        while (!myStack.empty()) {
            C &c = myStack.top();
            cout << "about to pop " << c << endl;
            myStack.pop();

        }
    }

    TEST(QueueQueue, queuePlay) {
        queue<C> myQueue;
        populate(myQueue, 0, 10);
        cout << endl;
        while (!myQueue.empty()) {
            C &c = myQueue.front();
            cout << "about to pop " << c << endl;
            myQueue.pop();
        }
    }




}