//
// Following web tutorial at:
// http://www.bogotobogo.com/cplusplus/multithreaded4_cplusplus11.php
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>
#include <thread>

using namespace std;


namespace  jsf2184 {
    TEST(BasicThreadTests, createAndJoin) {
        cout << endl;
        thread myThread([]() {
            cout << "Hi From Thread " << endl;
            sleep(1);
            cout << "Bye From Thread" << endl;
        });

        cout << "wait to join thread" << endl;
        myThread.join();
        cout << "join thread finished" << endl;
    }

    TEST(BasicThreadTests, createAndDetach) {
        cout << endl;
        thread myThread([]() {
            cout << "Hi From Thread " << endl;
            sleep(1);
            cout << "Bye From Thread" << endl;
        });

        cout << "detach thread" << endl;
        myThread.detach();
        cout << "main done" << endl;
    }

}