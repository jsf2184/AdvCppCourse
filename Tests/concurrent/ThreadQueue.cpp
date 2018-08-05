//
// Following web tutorial at:
// Concurrency Class: Section 3, Lesson 32
////

#include <iostream>
#include <gtest/gtest.h>
#include <numeric>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;


namespace  jsf2184 {

    // Head -> node -> node -> node   <- Tail
    //   Pop from the head
    //   Add at the tail.




    template <typename D>
    class ThreadQueue {

        class Node {
        public:
            Node(D &&data) {
                cout << "Node move constructor" << endl;
                _data = make_shared<D>(move(data));
                _next = nullptr;
            }
            Node(const D &data) {
                cout << "Node copy constructor" << endl;
                _data = make_shared<D>(data);
                _next = nullptr;
            }
            virtual ~Node() {
                cout << "Node::~Node()" << endl;
            }

            shared_ptr<D> _data;
            unique_ptr<Node> _next;
        };

    public:
        ThreadQueue() : _tail(nullptr), _head() {}

        void push(D &d) {
             Node *newNode = new Node(d);
             pushNewNode(newNode);
        }

        void push(D &&d) {
            Node *newNode = new Node(move(d));
            pushNewNode(newNode);
        }

        void pushNewNode(Node *newNode) {
            lock_guard<mutex> tailLock(_tailMutex);
            if (_tail) {
                _tail->_next = unique_ptr<Node>(newNode);
            } else {
                lock_guard<mutex> headLock(_headMutex);
                _head = unique_ptr<Node>(newNode);
            }
            _tail = newNode;
        }

        shared_ptr<D> pop() {
            lock_guard<mutex> headLock(_headMutex);
            if (!_head) {
                return shared_ptr<D>();
            }
            shared_ptr<D> res = _head->_data;
            _head = move(_head->_next);
            if (!_head) {
                lock_guard<mutex> tailLock(_tailMutex);
                _tail = nullptr;
            }
            return res;
        }

        bool isTailEmpty() {
            return _tail == nullptr;
        }

        bool isHeadEmpty() {
            return _head? false : true;
        }

    private:
        mutex _headMutex;
        mutex _tailMutex;
        condition_variable _cv;
        unique_ptr<Node> _head;
        Node *_tail;
    };

    class IntHolder {
    public:
        IntHolder(int val) : _val(val) {}
        IntHolder(const IntHolder &src) : _val(src._val) {
            cout << "IntHolder copy constructor" << endl;
        }
        IntHolder(const IntHolder &&src) : _val(src._val) {
            cout << "IntHolder move constructor" << endl;
        }

        virtual ~IntHolder() {
            cout << "IntHolder::~IntHolder() w/ _val = " << _val << endl;
        }

        int getVal() const {
            return _val;
        }
    private:
        int _val;
    };


    TEST(ThreadQueueTests, pushAndPop) {
        cout << endl;
        ThreadQueue<IntHolder> sut;
        cout << "pushing 0" << endl;
        sut.push(IntHolder(0));
        cout << "pushing 1" << endl;
        sut.push(IntHolder(1));
        cout << "pushing 2" << endl;
        sut.push(IntHolder(2));

        cout << "begin popping " << endl;
        while(!sut.isTailEmpty()) {
            shared_ptr<IntHolder> ptr = sut.pop();
            cout << ptr->getVal() << endl;
        }
        EXPECT_TRUE(sut.isHeadEmpty());
        EXPECT_TRUE(sut.isTailEmpty());
    }

    TEST(ThreadQueueTests, pushAndDestruct) {
        cout << endl;
        ThreadQueue<IntHolder> sut;
        cout << "pushing 0" << endl;
        sut.push(IntHolder(0));
        cout << "pushing 1" << endl;
        sut.push(IntHolder(1));
        cout << "pushing 2" << endl;
        sut.push(IntHolder(2));
    }


}