//
// Following web tutorial at:
// http://www.bogotobogo.com/cplusplus/multithreaded4_cplusplus11.php
//

#include <iostream>
#include <gtest/gtest.h>
#include <functional>
#include "../../ThreadGuard.h"

using namespace std;


namespace  jsf2184 {
    TEST(ThreadGuardTests, createAndJoinWithFunctor) {
        cout << endl;
        ThreadGuard tg1([] {sleep(1); cout << "hello from thread" << endl;});
    }

    ThreadGuard createThreadGuard(const string &msg) {
        ThreadGuard res([msg] {
            sleep(10);
            cout << "running thread w/msg = '" << msg << "'" << endl;
        });
        return res;
    }
    TEST(ThreadGuardTests, testCreateGuard) {
        cout << endl << "running testCreateGuard" << endl;
        ThreadGuard tg(createThreadGuard("passed in msg"));
        cout << "done with test" << endl;
    }

    TEST(ThreadGuardTests, useAssignOperator) {
        cout << endl;
        ThreadGuard tg1([] {sleep(5); cout << "hello from first thread" << endl;});
        tg1 = createThreadGuard("msg2");
        cout << "test is finished" << endl;
    }

}
