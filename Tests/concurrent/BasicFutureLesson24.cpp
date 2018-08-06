//
// Following web tutorial at:
// Concurrency Class: Section 2, Lesson 24
////
#include <iostream>
#include <gtest/gtest.h>
#include <numeric>
#include <future>

using namespace std;


namespace  jsf2184 {
    // Futures provide a way to wait on the results of a thread. It seems to have an implicit join() in it as well
    // as giving a thread a chance to return some work.
    
    int doSomeWorkInBackground(int n) {
        cout << "doSomeWorkInBackground(): performed from thread " << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "doSomeWorkInBackground(): done sleeping " << endl;
        return n;
    }
    
    TEST(BasicFutureTesting, simpleFutureTest) {
        cout << endl;
        cout << "Run launchFuture test" << endl;
        future<int> future = async(doSomeWorkInBackground, 5);
        int res = future.get();
        cout << "future returned: " << res << endl;
    }
    
}

