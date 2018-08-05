//
// Following web tutorial at:
// Concurrency Class: Section 2, Lesson 13
////


#include "../../ThreadVector.h"
#include <iostream>
#include <gtest/gtest.h>
#include <numeric>
#include <mutex>

using namespace std;


namespace  jsf2184 {

    class MutexSum {
    public:
        MutexSum() : _value(0){}
        void add(int v) {
            _mutex.lock();
            _value += v;
            _mutex.unlock();
        }
        
        int getVal() {
            int res;
            _mutex.lock();
            res = _value;
            _mutex.unlock();
            return res;
        }
    private:
        mutex _mutex;
        int _value;
    };

    class LockGuardSum {
    public:
        LockGuardSum() : _value(0){}
        void add(int v) {
            lock_guard<mutex> lg(_mutex);
            _value += v;
        }

        int getVal() {
            lock_guard<mutex> lg(_mutex);
            return _value;
        }
    private:
        mutex _mutex;
        int _value;
    };

    TEST(BasicMutexTest, TestMutexSum) {

        cout << endl;
        auto n = 29;
        ThreadVector threadVector;
        MutexSum sut;
        for (int i=0; i < n; i++) {
            threadVector.push_back([&sut, i]() {sut.add(i);});
        }
        threadVector.join();
        auto res = sut.getVal();
        auto expected = (n * (n - 1)) / 2;
        cout << "res = " << res << ", expected = " << expected << endl;
        EXPECT_EQ(expected, res);
    }

    TEST(BasicMutexTest, TestLgSum) {
        cout << endl;
        auto n = 29;
        ThreadVector threadVector;
        LockGuardSum sut;
        for (int i=0; i < n; i++) {
            threadVector.push_back([&sut, i]() {sut.add(i);});
        }
        threadVector.join();
        auto res = sut.getVal();
        auto expected = (n * (n - 1)) / 2;
        cout << "res = " << res << ", expected = " << expected << endl;
        EXPECT_EQ(expected, res);
    }

}

