//
// Section 4 Lesson 15 - Lists
//



#include <iostream>
#include <string>
#include <list>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;
using  jsf2184::C;

namespace {
    void populate(list<int> &res, int start, int count) {
        for (int i= 0; i<count; i++ ) {
            res.push_back(start+i);
        }
    }

    // Populate a list with our little 'C' class (whose constructor takes an integer)
    void populate(list<C> &res, int start, int count) {
        for (int i= 0; i<count; i++ ) {
            res.push_back(C(start+i));
        }
    }

    void print0(list<int> &list) {
        cout << endl;
        for (auto it = list.begin(); it != list.end(); it++) {
            cout << *it << endl;
        }
    }

    void printC(list<C> &list) {
        cout << endl;
        for (auto it = list.begin(); it != list.end(); it++) {
            cout << *it << endl;
        }
    }

    void prune0(list<int> &list) {
        for (auto it = list.begin(); it != list.end(); it++) {
            if (*it % 2 == 1) {
                it = list.erase(it);
            }
        }
    }

    void prune1(list<int> &list) {
        auto newEnd = remove_if(list.begin(),
                  list.end(),
                  [] (int v) {return v % 2 == 1;});
        list.erase(newEnd, list.end());
    }

    void pruneC(list<C> &list) {
        auto newEnd = remove_if(list.begin(),
                                list.end(),
                                [] (C &c) {return c.getX() % 2 == 1;});
        list.erase(newEnd, list.end());
    }

    void replace(list<C> &list) {
        C c(99);
        replace_if(list.begin(),
                                list.end(),
                                [] (C &c) {return c.getX() % 3 == 0;},
                                c);
    }


    TEST(StlLists, PopAndItereate) {
        list<int> list;
        populate(list, 0, 10);
        print0(list);
    }

    TEST(StlLists, PruneTestIterating) {
        list<int> list;
        populate(list, 0, 10);
        print0(list);
        prune0(list);
        cout << endl << "after pruning" << endl;
        print0(list);
    }

    TEST(StlLists, PruneTestLambda) {
        list<int> list;
        populate(list, 0, 10);
        print0(list);
        prune1(list);
        cout << endl << "after pruning" << endl;
        print0(list);
    }

    TEST(StlLists, PruneCLambda) {
        list<C> list;
        populate(list, 0, 10);
        printC(list);
        pruneC(list);
        cout << endl << "after pruning" << endl;
        printC(list);
        replace(list);
        printC(list);

    }

    string booleanStr(bool val) {
        return val ? "true" : "false";
    }
    void printItMatchesBeginningOrEnd(const string &label,
                                      list<int> &myList,
                                      list<int>::iterator &it)
    {
        cout << label
             << " == begin: "
             <<  booleanStr(it == myList.begin())
             << ", " << label
             << " == end: "
             << booleanStr(it == myList.end())
             <<endl;
    }


    TEST(StlLists, ListPlay) {
        cout << endl;
        list<int> myList;
        list<int>::iterator beginIt = myList.begin();
        list<int>::iterator endIt = myList.end();

        printItMatchesBeginningOrEnd("begin()", myList, beginIt);
        printItMatchesBeginningOrEnd("end()", myList, endIt);

        // Setup iterator to the end of the list. It is essentially a pointer to just past the last real node.
        list<int>::iterator it = myList.end();

        // The iterator 'it' stays pointed there as we insert successive items
        list<int>::iterator insertRes = myList.insert(it, 100);  // 100
        insertRes = myList.insert(it, 101);                      // 100, 101
        insertRes = myList.insert(it, 102);                      // 100, 101, 102
        insertRes = myList.insert(it, 103);                      // 100, 101, 102, 103

        print0(myList);  // 100, 101, 102, 103

        it = myList.begin();
        // it points at the first element: 100
        cout << "should be 100 and it is: "  << *it << endl; // points to 100

        // 'it' continues to point at the 100 and will throughout these inserts.
        // on the other hand, insertRes points at the item that was just inserted.

        insertRes = myList.insert(it, 96);
        print0(myList);  // 96, 100, 101, 102, 103
        cout << *insertRes << endl;  // 96

        insertRes = myList.insert(it, 97);
        print0(myList);  // 96, 97, 100, 101, 102, 103
        cout << *insertRes << endl;  // 97

        insertRes = myList.insert(it, 98);
        print0(myList);  // 96, 97, 98, 100, 101, 102, 103
        cout << *insertRes << endl;  // 98

        insertRes = myList.insert(it, 99);
        print0(myList);  // 96, 97, 98, 99, 100, 101, 102, 103
        cout << *insertRes << endl;   // 99


        // point to the 97
        auto eraseIt = myList.begin();
        eraseIt++;
        EXPECT_EQ(97, *eraseIt);
        cout << *eraseIt << endl;

        eraseIt = myList.erase(eraseIt);
        cout << "after erase, eraseIt points at " << *eraseIt << endl; // 98
        EXPECT_EQ(98, *eraseIt);

        while (eraseIt != myList.end()) {
            cout << "from erase loop, erase: " << *eraseIt << endl;
            eraseIt = myList.erase(eraseIt);
        }
        cout << "after the erase loop, here is myList" << endl;
        print0(myList);

    }


}
