//
// Section 4 Lesson 16 - Maps
//

#include <iostream>
#include <string>
#include<map>
#include <gtest/gtest.h>

using namespace std;

namespace {

    void populate(map<string, int> &ageMap) {
        ageMap["bob"] = 23;
        std::pair<string, int> pair = make_pair("jim", 24);
        ageMap.insert(pair);
        std::pair<string, int> pair2("alex", 25);
        ageMap.insert(pair2);
        auto pair3 = make_pair("zack", 22);
        ageMap.insert(pair3);
        ageMap.insert(make_pair("peter", 100));
    }

    void print(map<string, int> &map) {
        cout << endl << "printing map of size: " << map.size() << endl;
        for (auto it = map.begin(); it != map.end(); it++) {
            cout << it->first << "->" << it->second << endl;
        }
    }

    int get(map<string, int> &aMap, const string &k) {
        map<string, int>::iterator it =  aMap.find(k);
        if (it == aMap.end()) {
            return -1;
        }
        return it->second;

    }
    TEST(StlMaps, ItereateTest) {
        map<string, int> ageMap;
        populate(ageMap);
        print(ageMap);
    }

    TEST(StlMaps, RetrieveTest) {
        map<string, int> ageMap;
        populate(ageMap);
        EXPECT_EQ(23, get(ageMap, "bob"));
        EXPECT_EQ(24, get(ageMap, "jim"));
        EXPECT_EQ(22, get(ageMap, "zack"));
        EXPECT_EQ(25, get(ageMap, "alex"));
        EXPECT_EQ(-1, get(ageMap, "hank"));
    }

}
