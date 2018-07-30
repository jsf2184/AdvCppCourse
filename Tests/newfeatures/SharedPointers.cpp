//
// Section 8 Lesson 68
//

#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include "../../XX.h"

using namespace std;

namespace jsf2184 {


    TEST(SPTR_TESTS, ptrToInt) {
    }

    TEST(SPTR_TESTS, ptrToX) {
        shared_ptr<XX> ptr(new XX(3));
        EXPECT_EQ(3, ptr->getVal());

        {
            shared_ptr<XX> copy(ptr);
            EXPECT_EQ(3, copy->getVal());
            copy->setVal(4);
        }
        EXPECT_EQ(4, ptr->getVal());
    }

    TEST(SPTR_TESTS, makeSharedItem) {
        shared_ptr<XX> ptr = make_shared<XX>(3);
        EXPECT_EQ(3, ptr->getVal());
    }

    TEST(SPTR_TESTS, makeNullSharedPtr) {
        shared_ptr<XX> ptr;
        EXPECT_FALSE(ptr);
    }

    TEST(SPTR_TESTS, rawPtrExposure) {
        shared_ptr<XX> ptr = make_shared<XX>(3);
        XX *raw = ptr.get();

        EXPECT_EQ(3, raw->getVal());

        // But it is still owned by the SharedPtr too!
        EXPECT_EQ(3, ptr->getVal());
        EXPECT_TRUE(ptr);
    }

    TEST(SPTR_TESTS, ptrReset) {
        shared_ptr<XX> ptr = make_shared<XX>(3);
        EXPECT_EQ(3, ptr->getVal());
        EXPECT_TRUE(ptr);
        auto copy = ptr;
        EXPECT_EQ(2, ptr.use_count());
        EXPECT_EQ(2, copy.use_count());

        ptr.reset();
        EXPECT_FALSE(ptr);
        EXPECT_TRUE(copy);
        EXPECT_EQ(1, copy.use_count());
    }

    class MyBase {
    public:
        virtual int getX() { return 3; }
    };

    class MyDerived : public MyBase {
    public:
        int getX() { return 4; }
    };

    TEST(SPTR_TESTS, virtualWorks) {
        shared_ptr<MyBase> bPtr = make_shared<MyBase>();
        EXPECT_EQ(3, bPtr->getX());
        shared_ptr<MyDerived> dPtr = make_shared<MyDerived>();
        EXPECT_EQ(4, dPtr->getX());

        shared_ptr<MyBase> ptr = bPtr;
        EXPECT_EQ(3, ptr->getX());
        ptr = dPtr;
        EXPECT_EQ(4, ptr->getX());
    }

    TEST(SPTR_TESTS, arrayPlay) {
        cout << endl;
        shared_ptr<XX> xxBuf (new XX[3], [](XX *arr) {delete[] arr;});
        XX *xxPtr = xxBuf.get();
        xxPtr[0].setVal(0);
        xxPtr[1].setVal(1);
        xxPtr[2].setVal(2);
    }

    class Child;
    class Parent {
    public:
        Parent(const string &name) : _name(name) {
            cout << "Created Parent: " << _name << endl;
        }

        ~Parent() {
            cout << "Destroying Parent: " << _name << endl;
        }

        string getName() const {
            return _name;
        }

        void addChild(shared_ptr<Child> &child) {
            _children.push_back(child);
        }

        void report();

        static shared_ptr<Parent> createParent(const string &name, vector<string> kids) {
            shared_ptr<Parent> res = make_shared<Parent>(name);
            for (string kid : kids) {
                shared_ptr<Child> child = make_shared<Child>(kid, res);
                res->addChild(child);
            }
            return res;
        }

    private:
        vector<shared_ptr<Child>> _children;
        string _name;
    };

    class Child {
    public:
        Child(const string &name,
              const weak_ptr<Parent> &parent) : _name(name), _parent(parent) 
        {
            cout << "Created Child: " << _name << " with parent: " << getParentName() << endl;
        }

        virtual ~Child() {
            cout << "Destroying " << toLabel() << endl;
        }

        string getName() const {
            return _name;
        }
        
        string getParentName() const {
            if (!_parent.expired()) {
                const shared_ptr<Parent> &ptr = _parent.lock();
                string res = ptr->getName();
                return res;
            }
            return "";
        }
        string toLabel() const {
            ostringstream os;
            os << "Child: "
               << _name
               << " with parent: '"
               << getParentName()
               << "'"
               << ends;
            string res  = os.str();
            return res;
        }

    private:
        string _name;
        weak_ptr<Parent> _parent;
    };

    void Parent::report() {
        cout << "Parent: has name "
             << _name
             << " and "
             << _children.size()
             << " children"
             << endl;
        for_each(_children.begin(),
                 _children.end(),
                 [](shared_ptr<Child> child) {cout << child->toLabel() << endl;}
        );
    }

    TEST(SPTR_TESTS, parentChildPlay) {
        cout << endl;
        vector<string> kids = {"Alex", "Zack"};
        shared_ptr<Parent> jeff =  Parent::createParent("Jeff", kids);
        cout << "Jeff has been created" << endl;
        jeff->report();

    }

}