//
// Created by Jeffrey on 8/3/2018.
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>

using namespace std;


namespace  jsf2184 {

    enum MssOp {
        DefaultConstruct = 1,
        CopyConstruct = 2,
        MoveConstruct = 4,
        CopyAssign = 8,
        MoveAssign = 16
    };

    class MSS {
    public:
        explicit MSS(int x = 0) : _ops(DefaultConstruct) {
            cout << "MSS normal constructor" << endl;
        }

        MSS(const MSS &src) : _ops(CopyConstruct) {
            cout << "MSS copy constructor" << endl;
        }

        MSS(MSS &&src);

        MSS &operator=(const MSS &other) {
            _ops |= CopyAssign;
        }

        MSS &operator=(const MSS &&other) {
            _ops |= MoveAssign;
        }

        bool checkOp(MssOp op) {
            bool res = ((_ops & op) != 0);
            return res;
        }

    private:
        int _ops;
    };

    MSS::MSS(MSS &&src) : _ops(MoveConstruct) {
        cout << "MSS move constructor" << endl;
    }

    TEST(MSS_TESTS, testDefaultConstructor) {
        cout << endl;
        MSS sut;
        EXPECT_TRUE(sut.checkOp(DefaultConstruct));
        EXPECT_FALSE(sut.checkOp(CopyConstruct));
        EXPECT_FALSE(sut.checkOp(MoveConstruct));
        EXPECT_FALSE(sut.checkOp(CopyAssign));
        EXPECT_FALSE(sut.checkOp(MoveAssign));
    }

    TEST(MSS_TESTS, testCopyConstructor1) {
        cout << endl;
        MSS mss;
        MSS sut(mss);
        EXPECT_FALSE(sut.checkOp(DefaultConstruct));
        EXPECT_TRUE(sut.checkOp(CopyConstruct));
        EXPECT_FALSE(sut.checkOp(MoveConstruct));
        EXPECT_FALSE(sut.checkOp(CopyAssign));
        EXPECT_FALSE(sut.checkOp(MoveAssign));
    }

    TEST(MSS_TESTS, testCopyConstructor2) {
        cout << endl;
        MSS mss1;
        MSS sut = mss1;
        EXPECT_FALSE(sut.checkOp(DefaultConstruct));
        EXPECT_TRUE(sut.checkOp(CopyConstruct));
        EXPECT_FALSE(sut.checkOp(MoveConstruct));
        EXPECT_FALSE(sut.checkOp(CopyAssign));
        EXPECT_FALSE(sut.checkOp(MoveAssign));
    }

    MSS createMSS(int x) {
        return MSS(x);
    }

    TEST(MSS_TESTS, testMoveConstructor1) {
        cout << endl;
        MSS sut(createMSS(5));

        cout << "done constructing sut" << endl;
        EXPECT_FALSE(sut.checkOp(DefaultConstruct));
        EXPECT_FALSE(sut.checkOp(CopyConstruct));
        EXPECT_TRUE(sut.checkOp(MoveConstruct));
        EXPECT_FALSE(sut.checkOp(CopyAssign));
        EXPECT_FALSE(sut.checkOp(MoveAssign));
    }

    TEST(MSS_TESTS, testMoveConstructor2) {
        cout << endl;
        MSS sut(MSS(5));

        cout << "done constructing sut" << endl;
        EXPECT_FALSE(sut.checkOp(DefaultConstruct));
        EXPECT_FALSE(sut.checkOp(CopyConstruct));
        EXPECT_TRUE(sut.checkOp(MoveConstruct));
        EXPECT_FALSE(sut.checkOp(CopyAssign));
        EXPECT_FALSE(sut.checkOp(MoveAssign));
    }


    TEST(MSS_TESTS, testDefaultConstructorAndCopyAssignOp) {
        cout << endl;
        MSS mss1;
        MSS sut;
        sut = mss1;

        EXPECT_TRUE(sut.checkOp(DefaultConstruct));
        EXPECT_FALSE(sut.checkOp(CopyConstruct));
        EXPECT_FALSE(sut.checkOp(MoveConstruct));
        EXPECT_TRUE(sut.checkOp(CopyAssign));
        EXPECT_FALSE(sut.checkOp(MoveAssign));
    }

    TEST(MSS_TESTS, testDefaultConstructorAndMoveAssignOp) {
        cout << endl;
        MSS sut;
        sut = MSS(2);

        EXPECT_TRUE(sut.checkOp(DefaultConstruct));
        EXPECT_FALSE(sut.checkOp(CopyConstruct));
        EXPECT_FALSE(sut.checkOp(MoveConstruct));
        EXPECT_FALSE(sut.checkOp(CopyAssign));
        EXPECT_TRUE(sut.checkOp(MoveAssign));
    }

    class Holder1 {
    public:
        Holder1(const MSS &mss) : _mss(mss) {}
        Holder1(MSS &&mss) : _mss(move(mss)) {}
        bool checkOp(MssOp op) { return _mss.checkOp(op); }
    private:
        MSS _mss;
    };

    class Holder2 {
    public:
        Holder2(MSS mss) : _mss(move(mss)) {}
        bool checkOp(MssOp op) { return _mss.checkOp(op); }
    private:
        MSS _mss;
    };

    TEST(MSS_TESTS, testHolder1ValueConstructor) {
        cout << endl;
        MSS mss;  // normal constructor
        Holder1 holder1(mss);  // passed as ref, then copied into attribute.
        EXPECT_TRUE(holder1.checkOp(CopyConstruct));
//      Output:
//        MSS normal constructor
//        MSS copy constructor
    }

    TEST(MSS_TESTS, testHolder2ValueConstructor) {
        cout << endl;
        MSS mss; // normal constructor
        Holder2 holder2(mss); // copy constructor for param, move constructor for Holder attribute
        EXPECT_TRUE(holder2.checkOp(MoveConstruct));
//      Output:
//        MSS normal constructor
//        MSS copy constructor
//        MSS move constructor
    }


    TEST(MSS_TESTS, testHolder1MoveConstructor) {
        cout << endl;
        Holder1 holder1(createMSS(3));
        EXPECT_TRUE(holder1.checkOp(MoveConstruct));
//      Output:
//        MSS normal constructor
//        MSS move constructor     - to put result of createMSS() on the stack
//        MSS move constructor     - to move param into _mss attribute

    }

    void func(MSS &&mss) {
        cout << "In Func()" << endl;
    }
    TEST (MSS_TESTS, testRvaluePass) {
        cout << endl;
        func(createMSS(3));
//      Output:
//        MSS normal constructor
//        MSS move constructor  - to put result of createMSS() on the stack
//        In Func()
//      Confirming that
//        createMss() created an MSS object
//        and the move constructor was used to put it as the return on the stack
//        even though the calling code didn't care about the
//        createMss() return result.

    }

    TEST (MSS_TESTS, testRvalueCreate) {
        cout << endl;
        createMSS(3);
//      Output:
//        MSS normal constructor
//        MSS move constructor
//      Confirming that
//        createMss() created an MSS object
//        and the move constructor was used to put it as the return on the stack
//        even though the calling code didn't care about the
//        createMss() return result.
    }





}

