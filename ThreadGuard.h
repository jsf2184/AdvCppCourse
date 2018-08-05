//
// Created by Jeffrey on 7/31/2018.
//

#ifndef ADVCPPCOURSE_THREADGUARD_H
#define ADVCPPCOURSE_THREADGUARD_H
#include <thread>
#include <functional>
#include <iostream>

using namespace std;


class ThreadGuard {
public:
    ThreadGuard(thread &&aThread) : _thread(move(aThread)) {}
    ThreadGuard(function<void()> function) : _thread(function) {}
    ThreadGuard(ThreadGuard &&other) : _thread(move(other._thread)) {
        cout << "Move constructor" << endl;
    }

    ThreadGuard(const ThreadGuard &) = delete;

    virtual ~ThreadGuard() {
        cout << "ThreadGuard::~ThreadGuard() entry" << endl;
        if (_thread.joinable()) {
            cout << "ThreadGuard::~ThreadGuard() about to join" << endl;
            _thread.join();
        } else {
            cout << "ThreadGuard::~ThreadGuard() not joinable!" << endl;

        }
        cout << "ThreadGuard::~ThreadGuard() returning" << endl;
    }

    ThreadGuard &operator=(const ThreadGuard &) = delete;
    ThreadGuard &operator=(ThreadGuard && other) {
        // we have to first join the old thread that we've already got.
        cout << "Assignment operator entered" << endl;
        cout << "Assignment operator, onEntry, myThreadId = " << _thread.get_id() << ", otherId = " << other._thread.get_id() << endl;
        if (_thread.joinable()) {
            cout << "Assignment operator, start thread join" << endl;
            _thread.join();
            cout << "Assignment operator, finished thread join" << endl;
            cout << "Assignment operator, after join, myThreadId = " << _thread.get_id() << ", otherId = " << other._thread.get_id() << endl;
        }
        // and, now we need to get that other thread.
        cout << "Assignment operator, before assign, other._thread.joinable = " << other._thread.joinable() << endl;

        _thread = std::move(other._thread);
        cout << "Assignment operator, after assign, myThreadId = " << _thread.get_id() << ", otherId = " << other._thread.get_id() << endl;
        cout << "Assignment operator, after assign, other._thread.joinable = " << other._thread.joinable() << endl;
        cout << "Assignment operator, after assign, my _thread.joinable = " << _thread.joinable() << endl;
        cout << "Assignment operator returning" << endl;
        return *this;
    }


private:
    thread _thread;
};


#endif //ADVCPPCOURSE_THREADGUARD_H
