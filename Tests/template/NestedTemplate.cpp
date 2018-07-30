//
// Section 8 Lesson 43- A RingBuffer Class
//
// Note: instructor pretty much did not know what he was talking about for this lecture. He
// used a RingBuffer class that was far too complicated for the point he was trying to illustrate
// which, I think, was how to writer a CustomIterator. I did manage to get that working here for
// a simple fixed size vector class.
//

#include <iostream>
#include <string>
#include <gtest/gtest.h>

using namespace std;

namespace jsf2184 {

    template <typename T>
    class FixedVectorIterator {
    public:
        FixedVectorIterator(T *ptr) : _ptr(ptr) {}

        T &operator*() {
            return  *_ptr;
        }

        bool operator==(const FixedVectorIterator &other) const {
            return  _ptr == other._ptr;
        }

        bool operator!=(const FixedVectorIterator &other) const {
            return  ! operator==(other);
        }

        FixedVectorIterator &operator++(int) {
            _ptr++;
        }

        FixedVectorIterator &operator++() {
            _ptr++;
        }


    private:
        T *_ptr;
    };

    template<typename T>
    class FixedVector {
    public:

        FixedVector(int size) : _size(size), _writeIdx(0) {
            _array = new T[size];
        }
        ~FixedVector() {
            if (_array != nullptr) {
                delete[](_array);
                _array = nullptr;
            }
        }

        void add(initializer_list<T> values) {
            for (auto v : values) {
                add(v);
            }
        }
        void add(const T &val) {
            if (_writeIdx >= _size) {
                throw string("overwrote the end of the array");
            }
            _array[_writeIdx] = val;
            _writeIdx++;
        }

        int size() {
            return  _writeIdx;
        }

        typedef FixedVectorIterator<T> iterator;

        iterator begin() {
            return iterator(_array);
        }

        iterator end() {
            return iterator(_array + _writeIdx);
        }


    private:
        int _size;
        int _writeIdx;
        T  *_array;

    };


    TEST(CustomIteratorTests, tryIt) {
        cout << endl;
        FixedVector<int> a(10);
        a.add(1);
        a.add(2);
        a.add(3);
        for (auto it = a.begin(); it != a.end(); it++) {
            cout << *it << endl;
        }

        a.add({4, 5, 6});

        for (auto val : a) {
            cout << val << endl;


        }
    }

}
