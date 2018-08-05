//
// Following web tutorial at:
// Concurrency Class: Section 1, Lesson 10
////
#include "../../ThreadVector.h"
#include <iostream>
#include <gtest/gtest.h>
#include <numeric>
using namespace std;


namespace  jsf2184 {

    class Accumulator {
    public:
        Accumulator(const vector<int> &input, int numThreads)
                : _input(input), _numThreads(numThreads), _subTotals(numThreads)
        {
            setup(input, numThreads);
        }

        int checkResults() {
            _threadVector.join();
            int res = accumulate(_subTotals.begin(), _subTotals.end(), 0);
            return res;
        }

        static int addEm(const vector<int> &vec) {
            int res = std::accumulate(vec.begin(), vec.end(), 0);
            return res;
        }


    private:

        int rangeTotal(int idx,
                       vector<int>::const_iterator start,
                       vector<int>::const_iterator end )
        {
            int res = std::accumulate(start, end, 0);
            _subTotals[idx] = res;
            return res;
        }

        void setup(const vector<int> &input, int numThreads)
        {
            unsigned long remaining = input.size();
            unsigned long defBlockSize = (input.size() + numThreads - 1) / numThreads;
            int idx = 0;
            for (auto startR = input.begin(); startR <  input.end(); startR += defBlockSize) {
                unsigned long  numInSegment = std::min(defBlockSize, remaining);
                remaining -= numInSegment;
                auto endR = startR + numInSegment;
                cout << "start at " << *startR << endl;
                _threadVector.push_back([this, idx, startR, endR]() { return this->rangeTotal(idx, startR, endR); });

                //              function<int()> boundCall = bind(rangeTotal, this, idx, startR, endR);
//              _threadVector.push_back(thread(boundCall));
                idx++;
            }
        }

        const vector<int> &_input;
        vector<int> _subTotals;
        int _numThreads;
        ThreadVector _threadVector;
    };

    vector<int> populateVec(unsigned long n) {
        vector<int> res;
        res.reserve(n);
        for (int i=0; i<n; i++) {
            res.push_back(i);
        }
        return res;
    }

    void printVec(const vector<int> &vec) {
        for_each(vec.begin(), vec.end(), [](int v) {cout << v << endl;});
    }

    TEST(Accumulator_Test, TestPopVec) {
        cout << endl;
        vector<int> vec =  populateVec(29);
        printVec(vec);
    }

    TEST(Accumulator_Test, Constructor) {
        cout << endl;
        auto input = populateVec(29);
        Accumulator acc(input, 3);
        cout << "ready to check results" << endl;
        int answer1 = acc.checkResults();
        cout << "answer1 = " << answer1 << endl;
        int answer2 = acc.checkResults();
        cout << "answer2 = " << answer2 << endl;

        auto bruteAnswer = Accumulator::addEm(input);
        cout << "bruteAnswer = " << bruteAnswer << endl;

    }

}

