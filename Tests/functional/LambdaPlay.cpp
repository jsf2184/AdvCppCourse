//
// Section 8 Lesson 50,51,52 - Lambda
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>

using namespace std;


namespace  jsf2184 {
    
    TEST(LambdaPlayTests, assignAndCall) {
        cout << endl;

        // assign a lambda to the function pointer pFunction.
        void (*const pFunction)()=[]() {cout << "HelloWorld" << endl;};
        // invoke the function.
        pFunction();
    }

    class X {
    public:

        X() :X(0){}

        X(int val) : _val(val) {}

        void printHi() const {cout << "X.printHi() says: Hi" << endl;}
        void printHiWithArg(const string &arg) const {cout << "X.printHi() says: Hi to " << arg << endl;}

        X(const X &src) {
            std::cout << "X copy constructor" << endl;
            _val = src._val;
        }
        X & operator= (const X &src) {
            std::cout << "X operator =" << endl;
            _val = src._val;
        }

        int times(int mult) const{
            return _val * mult;
        }

        int getVal() const {
            return _val;
        }

        void setVal(int val) {
            _val = val;
        }
    private:
        int _val;
    };

    TEST(LambdaPlayTests, assignAndCallMethod) {
        cout << endl;
        X x;
        cout << "about to specify lambda" << endl;
        // here is a lambda that captures x (i.e. makes a copy of it)
        function<void()> pFunction =[x]() {x.printHi();};
        cout << "about to call lambda" << endl;
        pFunction();
    }

    void callWithPtrToFunction(void (*const pFunc)()) {
        cout << "about to call pFunc from callWithPtrToFunction " << endl;
        pFunc();
        cout << "done calling pFunc from callWithPtrToFunction " << endl;
    }

    TEST(LambdaPlayTests, passLambdaAsFunctionPtr) {
        cout << endl;
        callWithPtrToFunction([]() { cout << "hello" << endl; });
    }

    void callMethod(function<void()> funcObject) {
        cout << "about to call funcObject from callMethod() " << endl;
        funcObject();
        cout << "done calling funcObject from callMethod() " << endl;
    }


    TEST(LambdaPlayTests, passLambdaAsFunctionObject) {
        cout << endl;
        X x;
        callMethod([x]() { x.printHi(); });

        // without capturing.
        callMethod([]() { cout << "print directly" << endl; });
    }

    // std::function is a really good way to pass around a lambda. In this example,
    // our function returns an int and takes an int as an argument.
    //
    int callMethodWithArg(function<int(int x)> funcObject) {
        int res = funcObject(10);
        return res;
    }


    TEST(LambdaPlayTests, passLambdaWithArgAsFunctionObject) {
        cout << endl;
        X x(5);
        int res;
        res = callMethodWithArg([x](int p) {
            cout << "lambda called with value: " << p << endl;
            return x.times(p);
        });
        EXPECT_EQ(50, res);

        // without capturing.
        res = callMethodWithArg([](int p) {
            cout << "lambda called with value: " << p << endl;
            return p*p;
        });
        EXPECT_EQ(100, res);

    }


    template<typename Callable>
    void callTemplateLambda( Callable c) {
        cout << "about to call lambda as template " << endl;
        c();
        cout << "back from calling lambda as template " << endl;
    }

    TEST(LambdaPlayTests, passLambdaAsTemplate) {
        cout << endl;
        X x;
        callTemplateLambda([x]() {x.printHi();});
        callTemplateLambda([]() {cout << "print directly" << endl;});
    }

    template<typename Callable>
    int callTemplateLambdaWithArg( Callable c) {
        cout << "about to call lambda as template " << endl;
        int res = c(10);
        cout << "back from calling lambda as template " << endl;
        return res;
    }

    TEST(LambdaPlayTests, passLambdaAsTemplateWithArg) {
        cout << endl;
        X x(5);
        int res;
        res = callTemplateLambdaWithArg([x](int p) {return x.times(p);});
        EXPECT_EQ(50, res);
        // note syntax specifying explicit int return with '-> int' below.
        res = callTemplateLambdaWithArg([](int p) -> int { return p * p;});
        EXPECT_EQ(100, res);
    }


    TEST(LambdaPlayTests, captureVariablesByValue) {
        cout << endl;
        X x(5);
        int res;
        const auto c = [x](int p) {return x.times(p);};
        res = c(10);
        EXPECT_EQ(50, res);  // 5 * 10 50

        x.setVal(6);
        res = c(10); // so, with the answer be 6 * 10? or 5 * 10?
        // I am guessing 50 because I think the lambda captured a 'copy' of x back when its value was 5
        EXPECT_EQ(50, res);  // 5 * 10 50
    }

    TEST(LambdaPlayTests, captureVariablesByReference) {
        cout << endl;
        X x(5);
        int res;
        const auto c = [&x](int p) {return x.times(p);};
        res = c(10);
        EXPECT_EQ(50, res);  // 5 * 10 50

        x.setVal(6);
        res = c(10); // so, with the answer be 6 * 10? or 5 * 10?
        // I am guessing 60 because I think the lambda captured a reference to x and it changed to 6.
        EXPECT_EQ(60, res);  // 5 * 10 50
    }

    class Server {
    public:
        Server() {}
        void registerCallback(const function<void(int)> &client) {
            _client = client;
        }
        void invoke(int val) {
            _client(val);
        }
    private:
        function<void(int)> _client;

    };
//    class Client {
//    public:
//        Client(int val ,Server &server) : _val(val) {
//            server.registerCallback(&Client::onValue);
//        }
//        void onValue(int value) {
//            _val = value;
//        }
//    private:
//        int _val;
//    };

    class Client {
    public:
        Client(int val ,Server &server) : _val(val) {
            server.registerCallback([this](int value) {this->onValue(value);});
        }
        void onValue(int value) {
            _val = value;
        }
        int getVal() const {
            return _val;
        }
    private:
        int _val;
    };

    TEST(LambdaPlayTests, serverClientCallback) {
        Server server;
        Client client(0, server);
        server.invoke(10);
        EXPECT_EQ(10, client.getVal());
    }

    TEST(LambdaPlayTests, withMutableValueQualifier) {
        cout << endl;
        int x = 9;
        [x]() mutable {
            x = 5; // the mutable flag lets us change this value arg
            cout << "x is: " << x << endl;
        }();

        // but not outside the lambda.
        EXPECT_EQ(9, x);

    }

}
