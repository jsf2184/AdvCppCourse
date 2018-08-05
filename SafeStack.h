//
// Created by Jeffrey on 8/1/2018.
//

#ifndef ADVCPPCOURSE_SAFESTACK_H
#define ADVCPPCOURSE_SAFESTACK_H


#include <stdexcept>
#include <thread>
#include <mutex>

using namespace std;

class SafeStack {
    class Node {
    public:
        Node(int val, Node *next) : _val(val), _next(next) {}

        Node() : _val(-1), _next(nullptr){}

        int getVal() const {
            return _val;
        }

        Node *getNext() const {
            return _next;
        }

        void setNext(Node *next) {
            _next = next;
        }

    private:
        int _val;
        Node *_next;
    };
public:
    void push(int v) {
        lock_guard<mutex> lg(_mutex);
        Node *node = new Node(v, _head.getNext());
        _head.setNext(node);
    }
    bool isEmpty() {
        lock_guard<mutex> lg(_mutex);
        bool res = isEmptyInternal();
        return res;
    }
    int pop() {
        lock_guard<mutex> lg(_mutex);
        if (isEmptyInternal()) {
            throw runtime_error("illegal pop(): stack is empty");
        }
        Node *oldTop = _head.getNext();
        _head.setNext(oldTop->getNext());
        return oldTop->getVal();
    }

private:
    bool isEmptyInternal() {
        bool res = _head.getNext() == nullptr;
        return res;
    }

    Node _head;
    mutex _mutex;
};


#endif //ADVCPPCOURSE_SAFESTACK_H
