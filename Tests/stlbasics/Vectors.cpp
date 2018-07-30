//
// Section 4 Lesson 12 - Vectors
//


#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

using namespace std;

namespace  {
    void populate(vector<int> &vec, int start, int last) {
        for (int i=start; i<last; i++) {
            vec.push_back(i);
        }
    }

    TEST(StlVector, WierdPlay1) {
        cout << endl;
        vector<string> strings(4);
        strings[3] = "abc";
        // this would cause a coredump so commenting it out.
        // strings[4] = "def";
        for (int i=0; i<strings.size(); i++) {
            cout << "[" << i << "] '" << strings[i] << "'" << endl;
        }
    }

    TEST(StlVector, WierdPlay2) {
        cout << endl;
        vector<string> strings(4); // note that there are 4 blank elements at the beginning and "abc" will be the 4th element.
        strings.push_back("abc");
        for (int i=0; i<strings.size(); i++) {
            cout << "[" << i << "] '" << strings[i] << "'" << endl;
        }
    }

    TEST(StlVector, PopAndIterate) {
        cout << endl;
        vector<string> strings;
        strings.push_back("one");
        strings.push_back("two");
        strings.push_back("three");
        strings.push_back("four");

        for (int i=0; i<strings.size(); i++) {
            cout << strings[i] << endl;
        }

        for (ulong i=0; i<strings.size(); i++) {
            cout << strings.at(i) << endl;
        }

        for (auto iterator = strings.begin(); iterator < strings.end(); iterator++) {
            cout << *iterator << endl;
        }

        cout << "direct manipulation of iterator" << endl;
        const vector<string>::iterator iterator = strings.begin();
        cout << *iterator << endl;
        cout << *(iterator + 1) << endl;
        cout << *(iterator + 2) << endl;
        cout << *(iterator + 3) << endl;
        cout << *iterator << endl;
        cout << *(iterator + 1) << endl;
        cout << *(iterator + 2) << endl;
        cout << *(iterator + 3) << endl;

        if (iterator + 4 == strings.end()) {
            // this will print
            cout << "iterator + 4 == strings.end()" << endl;
        } else {
            cout << "iterator + 4 != strings.end()" << endl;
        }

    }

    TEST(StlVector, ChangeWithIterator) {
        vector<int> ints;
        populate(ints, 0, 10);

        for(auto it = ints.begin(); it < ints.end(); it++) {
            cout << *it << endl;
        }
        for( vector<int>::iterator  it = ints.begin(); it < ints.end(); it++) {
            *(it) *= 2;
        }

        for(auto it = ints.cbegin(); it < ints.cend(); it++) {
            cout << *it << endl;
        }

    }


    void print(const vector<int>::iterator &start, const vector<int>::iterator &finish) {
        cout << endl;
        for (auto it = start; it != finish; it++) {
//            cout << typeid(it).name() << endl;
            cout << *it << " ";
        }
        cout << endl;
    }



    void print(vector<int> & vec) {
        print(vec.begin(), vec.end());
    }

    void doubleVec(const vector<int>::iterator &start, const vector<int>::iterator &finish) {
        vector<int, std::allocator<int>>::iterator iter = start;
        for (auto it = start; it != finish; it++) {
            *it *= 2;
        }
    }

    TEST(StlVector, ConstRefFromBeginIterPlay) {
        vector<int> vec;
        populate(vec, 0, 10);

        const vector<int, std::allocator<int>>::iterator &iterRef = vec.begin();
        // iterRef++;  //can't make refElem0 point to a different element cuz it is const.

        // but we can change what is stored at the iterator.
        *iterRef += 100;

        EXPECT_EQ(100, *iterRef);
        vector<int, std::allocator<int>>::iterator iterCopy = iterRef;
        iterCopy++;
        *iterCopy += 100;
        EXPECT_EQ(101, *iterCopy);


    }

//    TEST(StlVector, PlainRefFromBeginIterPlay) {
//
//        vector<int> vec;
//        populate(vec, 0, 10);
//
//        //can't make refElem0 point to a different element cuz it is const
//         vector<int, std::allocator<int>>::iterator &iterRef = vec.begin();
//         iterRef++;
//
//        // but we can change what is stored at the iterator.
//        *iterRef += 100;
//        EXPECT_EQ(100, *iterRef);
//
//    }

//    TEST(StlVector, onstIteratorRefPlay) {
//        vector<int> vec;
//        populate(vec, 0, 10);
//
//        const vector<int, std::allocator<int>>::const_iterator &iter = vec.cbegin();
////        iter++;
//
//        // but we can change what is stored at the iterator.
//        *iter += 100;
//    }


    TEST(StlVector, RefIteratorPlay) {
        vector<int> vec;
        populate(vec, 0, 10);
        vector<int, std::allocator<int>>::iterator iter1 = vec.begin();
        iter1++; // iter1 points to element at idx 1 now.
        *iter1 += 100;
        EXPECT_EQ(101, *iter1);
        cout << "iter1 points at value: " << *iter1 << endl;

        vector<int, std::allocator<int>>::iterator &refIter1 = iter1;
        refIter1++;  // now refIter1 has been moved forward to the element at idx 2.
        *refIter1 += 100;
        EXPECT_EQ(102, *refIter1);
        EXPECT_EQ(102, *iter1);
        cout << "iter1 points at value: " << *iter1 << ", refIter1 points at value: " << *refIter1 << endl;
    }


    TEST(StlVector, RemoveIfAndEraseWithIterator) {
        vector<int> vec;
        populate(vec, 0, 10);

        auto it = find(vec.begin(), vec.end(), 7);
        EXPECT_EQ(7, *it);

        // Note that remove_if() is a std algorithm that can be used with lots of collections (not
        // just vectors). With this generality, it can't actually delete elements, it can only
        // shuffle things around.
        //
        auto origSize = vec.size();
        auto newEnd = remove_if(vec.begin(), vec.end(), [] (int v) { return v % 2 == 1;});
        auto  postRemoveSize = vec.size();

        // so, there are now still 10 elements
        EXPECT_EQ(origSize, postRemoveSize);
        print(vec);

        cout << "after remove, it points to " << *it << endl;
        vec.erase(newEnd, vec.end());
        cout << "after erase, it points to " << *it << endl;
        print(vec);
    }

    TEST(StlVector, DoItYourselfEraseWithIterator) {
        cout << endl;
        vector<int> vec;
        populate(vec, 0, 10);
        print(vec);

        for (auto it = vec.begin(); it != vec.end(); it++) {
            if (*it % 2 == 0) {
                vec.erase(it);
            }
        }
        print(vec);
    }

}

