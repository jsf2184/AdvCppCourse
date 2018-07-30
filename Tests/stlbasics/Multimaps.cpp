//
// Section 4 Lesson 18 - Maps With Custom Class As Key
//

#include <iostream>
#include <map>
#include <string>
#include <gtest/gtest.h>

using namespace std;

namespace {

    void populate(multimap<int, int> &aMap) {
        for (int i=2; i<= 10; i+=2) {
            aMap.insert(make_pair(i, i*2));
        }
    }

    void print(const multimap<int, int>::const_iterator start,  const multimap<int, int>::const_iterator finish) {
        cout << endl;
        for (auto it=start; it != finish; it++) {
            cout << it->first <<  " : " << it->second << endl;
        }

    }

//    void print(multimap<int, int, std::less<int>, std::allocator<std::pair<const int, int>>>::const_iterator iterator,
//           multimap<int, int, std::less<int>, std::allocator<std::pair<const int, int>>>::const_iterator const_iterator) {
//
//    }

    void print(const multimap<int, int> &aMap) {
        print(aMap.begin(), aMap.end());
    }

    
    TEST(StlMultiMap, IterateTest) {
        multimap<int, int> aMap;
        populate(aMap);
        print(aMap);

        // add in a duplicate for each key.
        populate(aMap);
        print(aMap);

        cout << "try to find an element that is not there." << endl;
        // nothing should print
        auto iterator = aMap.find(3);
        print(iterator, aMap.end());

        cout << "try to find an element that is there." << endl;
        // the desired element and all past it should print: 4,4,6,6,8,8,10,10
        iterator = aMap.find(4);
        print(iterator, aMap.end());

        cout << "try to find only the desired element(s) that are there." << endl;
        // the desired element and all past it should print: 4,4
        auto pair = aMap.equal_range(4);
        print(pair.first, pair.second);

        cout << "try to find element(s) in range 5 thru 9" << endl;
        // the desired element and all past it should print: 4,4
        auto lowerBound = aMap.lower_bound(5); // first one for which 5 is not lower
        auto upperBound = aMap.upper_bound(9); // last one for which 9 is not higher
        print(lowerBound, upperBound); // 6,6,8,8

        cout << "try to find element(s) in range 6 thru 8" << endl;
        // the desired element and all past it should print: 4,4
        lowerBound = aMap.lower_bound(6); // first one for which 5 is not lower
        upperBound = aMap.upper_bound(8); // last one for which 8 is not higher
        print(lowerBound, upperBound); // 6,6,8,8


    }

}
