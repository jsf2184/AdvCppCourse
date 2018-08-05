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

    class RunClass {
    public:
        void operator()() {
            cout << "Hello From Run Class" << endl;
            sleep(2);
            cout << "Bye From Run Class" << endl;
        }
    };

    TEST(BasicThreadTests, createAndJoinWithFunctor) {
        cout << endl;

        RunClass runClass;
        thread myThread(runClass);
        cout << "wait to join thread" << endl;
        myThread.join();
        cout << "join thread finished" << endl;
    }

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
        sleep(3);
        cout << "main done" << endl;
    }

    enum ThreadAction {
        Join,
        Detach,
        Ignore
    };

    void threadCreatorOld(unsigned int preSleep,
                          unsigned int postSleep,
                          unsigned int launcherSleep,
                          ThreadAction threadAction) {
        thread myThread([=]() {
            if (preSleep != 0) {
                sleep(preSleep);
            }
            cout << "thread: Hi From Thread " << endl;
            if (postSleep != 0) {
                sleep(postSleep);
            }
            cout << "thread: Bye From Thread" << endl;
        });

        if (launcherSleep != 0) {
            sleep(launcherSleep);
        }
        bool wasJoinable = myThread.joinable();
        switch (threadAction) {
            case Join:
                cout << "main: about to initiate join" << endl;
                myThread.join();
                cout << "main: back from join" << endl;
                break;
            case Detach:
                cout << "main: about to initiate detach" << endl;
                myThread.detach();
                cout << "main: back from detach" << endl;
                break;
            case Ignore:
                cout << "main: back from ignore" << endl;
                break;
        }
        cout << "main: Note that threadWasJoinable = " << wasJoinable << endl;
    }


    thread createThread(unsigned int preSleep,
                        unsigned int postSleep) {
        thread myThread([=]() {
            if (preSleep != 0) {
                sleep(preSleep);
            }
            cout << "thread: Hi From Thread " << endl;
            if (postSleep != 0) {
                sleep(postSleep);
            }
            cout << "thread: Bye From Thread" << endl;
        });
        return myThread;
    }

    void threadCreator(unsigned int preSleep,
                       unsigned int postSleep,
                       unsigned int launcherSleep,
                       ThreadAction threadAction) {
        thread myThread = createThread(preSleep, postSleep);
        if (launcherSleep != 0) {
            sleep(launcherSleep);
        }
        bool wasJoinable = myThread.joinable();
        switch (threadAction) {
            case Join:
                cout << "main: about to initiate join" << endl;
                myThread.join();
                cout << "main: back from join" << endl;
                break;
            case Detach:
                cout << "main: about to initiate detach" << endl;
                myThread.detach();
                cout << "main: back from detach" << endl;
                break;
            case Ignore:
                cout << "main: back from ignore" << endl;
                break;
        }
        cout << "main: Note that threadWasJoinable = " << wasJoinable << endl;
    }


    TEST(BasicThreadTests, launcherDetachesBeforeThreadCompletes) {
        cout << endl;
        cout << "main: about to call thread creator" << endl;
        threadCreator(1, 1, 0, Detach);
        cout << "main: back from thread creator" << endl;
//        sleep(3);
        cout << "main: done" << endl;
    }

    TEST(BasicThreadTests, launcherDetachesAfterThreadCompletes) {
        cout << endl;
        cout << "main: about to call thread creator" << endl;
        threadCreator(1, 1, 5, Detach);
        cout << "main: back from thread creator" << endl;
//        sleep(3);
        cout << "main: done" << endl;
    }

    TEST(BasicThreadTests, launcherJoinsBeforeThreadCompletes) {
        cout << endl;
        cout << "main: about to call thread creator" << endl;
        threadCreator(1, 1, 0, Join);
        cout << "main: back from thread creator" << endl;
//        sleep(3);
        cout << "main: done" << endl;
    }

    TEST(BasicThreadTests, launcherJoinsAfterThreadCompletes) {
        cout << endl;
        cout << "main: about to call thread creator" << endl;
        threadCreator(1, 1, 5, Join);
        cout << "main: back from thread creator" << endl;
//        sleep(3);
        cout << "main: done" << endl;
    }

    TEST(BasicThreadTests, launcherIgnoresAfterThreadCompletes) {
        cout << endl;
        cout << "main: about to call thread creator" << endl;
        try {
            threadCreator(1, 1, 5, Ignore);
        } catch (...) {
            cout << "main: caught excecption from threadCreator" << endl;
        }
        cout << "main: back from thread creator" << endl;
//        sleep(3);
        cout << "main: done" << endl;
    }

    TEST(BasicThreadTests, createThreadWithValueArgs) {
        cout << endl;
        thread myThread([](int x, int y) {
            sleep(1);
            cout << "The sum is " << x + y << endl;
        }, 3, 4);
        myThread.join();
    }

    TEST(BasicThreadTests, createThreadWithRefArgs) {
        cout << endl;
        int val = 10;
        int limit = 20;
        thread myThread([](int &ref, int stopper) {
            while(ref != stopper) {
                sleep(1);
                cout << "ref is " << ref << endl;
            }
            cout << "ref = " << ref << " and stopper = " << stopper << endl;
        }, ref(val), limit);
        while (val != limit) {
            val++;
            sleep(1);
        }
        myThread.join();
    }


    TEST(BasicThreadTests, callHardwareConcurrencyFunc) {
        cout << endl;
        cout << "hardeareConcurrency() returns " <<  thread::hardware_concurrency() << endl;
    }

    TEST(BasicThreadTests, callSleepForAndGetId) {
        cout << endl;
        thread myThread([] (int ms) {
            this_thread::sleep_for(chrono::milliseconds(ms));
            cout << "thread w/id = " <<  this_thread::get_id() << " just slept for " << ms  << " ms " << endl;
        }, 37);
        cout << "waiting for thread w/id = " << myThread.get_id() << endl;
        myThread.join();
        cout << "done" << endl;
    }

    TEST(BasicThreadTests, testDefaultThread) {
        cout << endl;
        thread myThread;
        cout << "default threadid = "  << myThread.get_id() << " and joinable = " << myThread.joinable() << endl;
    }

}