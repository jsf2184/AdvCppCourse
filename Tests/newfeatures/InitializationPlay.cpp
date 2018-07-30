//
// Section 8 Lesson 45, 46
//


#include <iostream>
#include <gtest/gtest.h>
#include <list>
#include <initializer_list>

using namespace std;

namespace jsf2184 {
    class V {
    public:

        V(int x, int y) : _x(x), _y(y) {}

        V() : _x(-1), _y(-1) {}

        int _x;
        int _y;

        friend ostream &operator<<(ostream &os, const V &v) {
            os << "_x: " << v._x << " _y: " << v._y;
        }
    };

    void printArray(int arr[], int size) {
        cout << endl;
        for (int i = 0; i < size; i++) {
            cout << arr[i] << endl;
        }
    }

    TEST(INIT_TESTS, arrayInit) {

        int a[] = {1, 2, 3};
        printArray(a, 3);

        int b[]{1, 2, 3};
        printArray(b, 3);

        int *c = new int[3]{1, 2, 3};
        printArray(c, 3);
        delete[] c;

        int *d{new int[3]{1, 2, 3}};
        printArray(d, 3);
        delete[] d;

        int e[3]{};
        printArray(e, 3);

    }

    TEST(INIT_TESTS, structInit) {
        V v = {3, 4};
        cout << endl << v << endl;
    }

    TEST(INIT_TESTS, structArrayInit) {

        V *vPtr{new V[2]{{3, 4},
                         {5, 6}}};
//      Note: can't do range based loop since it doesn't know how many there are.
//        for (auto v : vPtr ) {
//            cout << v << endl;
//        }

        // But here, it knows there are 2 elements.
        V vArr[] = {{3, 4},
                    {5, 6}};
        cout << endl;
        for (auto v : vArr) {
            cout << v << endl;
        }
        int size = std::extent<decltype(vArr)>::value;


        V vArr2[3] = {};
        cout << endl;
        for (auto v : vArr2) {
            cout << v << endl;
        }


    }

    TEST(INIT_TESTS, vectorInit) {
        vector<V> vec = {{3, 4},
                         {5, 6}};
        cout << endl;
        for (auto v : vec) {
            cout << v << endl;
        }
    }

    TEST(INIT_TESTS, vectorInit2) {
        vector<V> vec = {V(3, 4), V{5, 6}};
        cout << endl;
        for (auto v : vec) {
            cout << v << endl;
        }
    }

    TEST(INIT_TESTS, listInit) {
        list<V> l = {{3, 4},
                     {5, 6}};
        cout << endl;
        for (auto v : l) {
            cout << v << endl;
        }
    }

    TEST(INIT_TESTS, listInit2) {
        list<V> l = {V(3, 4), V{5, 6}};
        cout << endl;
        for (auto v : l) {
            cout << v << endl;
        }
    }

    TEST(INIT_TESTS, intInit) {
        int x = 1;
        int y(2);
        int z{3};
        cout << endl << x << y << z << endl;
    }

    class InitListUser {
    public:
        InitListUser(initializer_list<int> ilist) {
            for (auto i :ilist) {
                _vec.push_back(i);
            }
        }

        friend ostream &operator<<(ostream &os, const InitListUser &ilu) {
            for (auto i : ilu._vec) {
                os << i << " ";
            }
            return os;
        }

    private:
        vector<int> _vec;
    };

    TEST(INIT_TESTS, initializerList) {
        cout << endl;
        InitListUser sut{1, 2, 3, 4};
        cout << sut << endl;

        initializer_list<int> ilist {1, 2, 3, 4};
        for (auto i : ilist) {
            cout << i << endl;
        }
    }
}

