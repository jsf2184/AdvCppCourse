//
// Following web tutorial at:
// Concurrency Class: Section 2, Lesson 21
////
#include "../../ThreadVector.h"
#include <iostream>
#include <gtest/gtest.h>
#include <numeric>
#include <thread>
#include <condition_variable>

using namespace std;


namespace  jsf2184 {
    class Progress {
    public:
        Progress(int remainingDistance) : _remainingDistance(remainingDistance) {
        }

        bool takeStep() {
            unique_lock<mutex> ul(_mutex);
            _remainingDistance--;
            if (_remainingDistance == 0) {
                _cv.notify_all();
                return false;
            }
            return true;
        }

        int wait() {
            unique_lock<mutex> ul(_mutex);
            _cv.wait(ul, [this]() {return this->_remainingDistance == 0;});
            return _remainingDistance;
        }

    private:
        int _remainingDistance;
        mutex _mutex;
        condition_variable _cv;
    };

    TEST(ConditionVariablePlay, SimpleNotify) {
        cout << endl;
        Progress progress(10);
        thread observer([&progress ](){
            cout << "observer starting to wait" << endl;
            int remainingDistance = progress.wait();
            cout << "observer done waiting w/remainingDistance = " << remainingDistance << endl;
        });
        thread traveler([&progress]() {
            while(progress.takeStep()) {
                cout << "traveler taking another step" << endl;
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            cout << "traveler finished" << endl;
        });

        observer.join();
        traveler.join();
    }

}
