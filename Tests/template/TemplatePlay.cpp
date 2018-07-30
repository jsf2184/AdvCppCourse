//
// Created by Jeffrey on 5/27/2018.
//

#include <iostream>
#include <gtest/gtest.h>
#include "../../C.h"

using namespace std;

namespace  jsf2184 {

    class HasX {
        virtual ~HasX(){}
        virtual int getX() = 0;
    };


    // Use XHolder class to demonstrate what happens if we make an
    // assumption that 'T' has a getX() method. C++ allows us to
    // make the call here. If the templated type does not have
    // a getX() method, we find out when we invoke the template, not here.
    //
    template <class T>
    class XHolder {
    public:
        XHolder(T actual) : _actual(actual) {
        }

        int getX() {
            return _actual.getX();
        }
    private:
        T _actual;
    };

    class D {
    public:
        D() {cout << "D constructor" << endl;}
    };


    // Note that Class E and Class F below are in no way related, yet both have a run()
    // method and we can use templates to simulate a virtual call to the appropriate
    // run method.
    //
    class E  {
    public:
        E() {cout << "E constructor" << endl;}
        void run() {cout << "E running" << endl;}
    };

    class F {
    public:
        F() {cout << "F constructor" << endl;}
        void run() {cout << "F running" << endl;}
    };

//    template<class T>
//    T create() {
//        return T();
//    }

    class BaseVirtualRunner {
    public:
        virtual ~BaseVirtualRunner(){
            cout << "BaseVirtualRunner::~BaseVirtualRunner()" << endl;
        }
        virtual void mainLoop() = 0;
    };

    
    template<class T>
    class FakeVirtualRunner : public BaseVirtualRunner{
    public:
        FakeVirtualRunner(T worker) : _worker(worker) {}

        virtual ~FakeVirtualRunner() {
            cout << "FakeVirtualRunner::~FakeVirtualRunner()" << endl;
        }

        void mainLoop() {
            cout << "FakeVirtualRunner::mainLoop() " << endl;
            for (int i=0; i<2; i++) {
                _worker.run();
            }
        }

    private:
        T _worker;
    };


    template<typename T>
    void print(T t) {
        cout << "templatePrint(): " << t << endl;
    }

    void print(int t) {
        cout << "nonTemplatePrint(): " << t << endl;
    }

    TEST(TemplatePlayTests, HasXTest) {
        XHolder<C> xHolder(C(3));
        EXPECT_EQ(3, xHolder.getX());
    }

    TEST(TemplatePlayTests, NoXTest) {
        /* wont compile because D has no getX() method
          XHolder<D> xHolder(D(3));
          EXPECT_EQ(3, xHolder.getX());
        */
    }

    TEST(TemplatePlayTests, printTest) {
        // type inference helps us out here
        cout << endl;
        print(5);
        print<>(6);
        print("hello");
    }

    // A simple factory method to create the right templated type of BaseVirtualRunner
    BaseVirtualRunner *create(char kind) {
        cout << endl;
        switch(kind) {
            case 'E':
                return new FakeVirtualRunner<E>(E());
                break;
            case 'F':
                return new FakeVirtualRunner<F>(F());
                break;
            default:
                return nullptr;
        }
    }
    
    void createAndRun(char kind) {
        BaseVirtualRunner *const runner = create(kind);
        runner->mainLoop();
        delete runner;
    }

    TEST(TemplatePlayTests, createAndRunIt) {
        // type inference helps us out here
        cout << endl << endl;

        createAndRun('E');
        createAndRun('F');

    }

}

