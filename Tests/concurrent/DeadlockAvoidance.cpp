//
// Following web tutorial at:
// Concurrency Class: Section 2, Lesson 19
////
#include "../../ThreadVector.h"
#include <iostream>
#include <gtest/gtest.h>
#include <numeric>
#include <mutex>

using namespace std;

namespace  jsf2184 {
    class Account {
    public:
        Account(int balance) : _balance(balance) {}
        void takeOne(Account &other) {
            unique_lock<mutex>  myLock(_mutex, defer_lock);
            unique_lock<mutex>  otherLock(other._mutex, defer_lock);
            lock(myLock, otherLock);
            _balance += 1;
            other._balance -= 1;
        }

        int getBalance() const {
            return _balance;
        }

    private:
        int _balance;
        mutex _mutex;
    };
    
    void runIt(Account &a, Account &b, int amount) {
        // Try to take all of b's money and add it to a.
        cout << "runIt() onEntry: take=" << amount <<  ", a=" << a.getBalance() << ", b=" << b.getBalance() << endl;
        for (int i=0; i<amount; i++) {
            a.takeOne(b);
        }
    }
    
    TEST(AVOID_DLOCK, testItSingleThreaded) {
        cout << endl;
        int amt1 = 1000;
        int amt2 = 2000;
        Account a1(amt1);
        Account a2(amt2);
        runIt(a1, a2, amt2);
        cout << "After 1st run, a1=" << a1.getBalance() << ", a2=" << a2.getBalance() << endl;
        runIt(a2, a1, amt1);
        cout << "After 2nd run, a1=" << a1.getBalance() << ", a2=" << a2.getBalance() << endl;

        // They should have switched amounts.
        EXPECT_EQ(amt1, a2.getBalance());
        EXPECT_EQ(amt2, a1.getBalance());
    }

    TEST(AVOID_DLOCK, testDoubleThreaded) {
        cout << endl;
        int amt1 = 1000;
        int amt2 = 2000;
        Account a1(amt1);
        Account a2(amt2);
        thread t1([&a1, &a2, amt2]() {runIt(a1, a2, amt2);});
        thread t2([&a1, &a2, amt1]() {runIt(a2, a1, amt1);});

        t1.join();
        t2.join();
        cout << "After runs, a1=" << a1.getBalance() << ", a2=" << a2.getBalance() << endl;

        // They should have switched amounts.
        EXPECT_EQ(amt1, a2.getBalance());
        EXPECT_EQ(amt2, a1.getBalance());
    }


}


