//
// Created by Jeffrey on 8/1/2018.
//

#ifndef ADVCPPCOURSE_THREADVECTOR_H
#define ADVCPPCOURSE_THREADVECTOR_H

#include <vector>
#include <functional>
#include <thread>
#include <algorithm>

using namespace std;

namespace  jsf2184 {

    class ThreadVector {
    public:
        void push_back(function<void()> runnable) {
            _threads.push_back(thread(runnable));
        }
        void join() {
            for_each(_threads.begin(),
                     _threads.end(),
                     [](thread &t) {if (t.joinable()) t.join();}
            );
        }
    private:
        vector<thread> _threads;
    };

}
#endif //ADVCPPCOURSE_THREADVECTOR_H
