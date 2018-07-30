//
// Section 4 Lesson 23- Maps With Custom Class As Key
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;

namespace  {

    void populate(map<string, vector<int>> &scores) {
        scores["Bob"].push_back(80);
        scores["Bob"].push_back(90);
        scores["Bob"].push_back(60);

        scores["Sue"].push_back(32);
        scores["Sue"].push_back(42);
    }
    
    TEST(NestedCollections, popAndPrint) {
        map<string, vector<int>> scores;
        populate(scores);
        cout <<endl;
        for (auto it = scores.begin(); it != scores.end(); it++) {
            const string &name = it->first;
            const vector<int> &list = it->second;
            cout << name << ": " ;
            for (auto sit = list.begin(); sit < list.end(); sit++) {
                const int &score = *sit;
                cout << score << " ";
            }
            cout << endl;
        }
    }

}
