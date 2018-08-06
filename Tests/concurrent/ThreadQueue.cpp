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
            Node() {
            }
            virtual ~Node() {
                cout << "Node::~Node()" << endl;
            }
            shared_ptr<D> _data;
            unique_ptr<Node> _next;
        };

    public:
        ThreadQueue() : _head(new Node()), _tail(_head.get()) {
            // We construct our empty ThreadQueue with head and tail both pointing at a 'dummy' node.
            // There will always be one such node.
            // Note that it won't always be the same dummy node however.
        }

        void push(D &d) {
            shared_ptr<D> sharedPtr = make_shared<D>(d);
            push(sharedPtr);
        }

        void push(D &&d) {
            shared_ptr<D> sharedPtr = make_shared<D>(move(d));
            push(sharedPtr);
        }
        
        void push(shared_ptr<D> &dataPtr) {
            // we need a new dummy node.
            unique_ptr<Node> newDummy(new Node());
            Node *newTail = newDummy.get();
            {
                // guard the tail.
                lock_guard<mutex> tlg(_tailMutex);
                // install our data into the old dummy node (on its way to not being a dummy node anymore)
                _tail->_data = dataPtr;
                // give that formerly dummy node a unique_ptr to the new dummy.
                _tail->_next = move(newDummy);
                // make the tail point to the newTail
                _tail = newTail;
            }
            _cv.notify_all();
        }

        Node *getTailSafely() {
            lock_guard<mutex> tlg(_tailMutex);
            return _tail;
        }

        bool isEmpty() {
            lock_guard<mutex> hlg(_headMutex);
            return _head.get() == getTailSafely();
        }

        shared_ptr<D> pop() {
            lock_guard<mutex> hlg(_headMutex);
            if (_head.get() == getTailSafely()) {
                return shared_ptr<D>();
            }
            // capture the data from the old head
            shared_ptr<D> res = _head->_data;
            // Assign the nextPtr from the old head to the current head. This is also going to delete the old head.
            _head = move(_head->_next);
            return res;
        }

        shared_ptr<D> popWait() {
            unique_lock<mutex> headLock(_headMutex);
            _cv.wait(headLock, [this] () {
                return this->_head.get() != this->getTailSafely();
            });

            // capture the data from the old head
            shared_ptr<D> res = _head->_data;
            // Assign the nextPtr from the old head to the current head. This is also going to delete the old head.
            _head = move(_head->_next);
            return res;
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
        while(shared_ptr<IntHolder> ptr = sut.pop()) {
            cout << ptr->getVal() << endl;
        }
        EXPECT_TRUE(sut.isEmpty());
        cout << "done popping " << endl;
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

    TEST(ThreadQueueTests, multithreadWriterAndReader) {
        cout << endl;
        ThreadQueue<IntHolder> sut;
        vector<int> readVec;
        thread reader([&]() {
            while(shared_ptr<IntHolder> ptr = sut.popWait()) {
                int val = ptr->getVal();
                readVec.push_back(val);
                if (val == 0) {
                    break;
                }
            }
        });
        for (int i=9; i>=0; i--) {
            shared_ptr<IntHolder> sptr = make_shared<IntHolder>(i);
            sut.push(sptr);
        }
        cout << "about to call reader.join()" << endl;
        reader.join();
        cout << "reader.join() completed!" << endl;

        unsigned long numRead = readVec.size();
        cout << numRead << " values were read" << endl;
        EXPECT_EQ(10, numRead);

        for (int i=0; i<10; i++) { 
            int val = readVec[i];
            cout << "reader read value: " << val << " at position " << i << endl;
            EXPECT_EQ(9-i, val);
        }
    }


}