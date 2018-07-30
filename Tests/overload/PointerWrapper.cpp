//
// Section 5 Lesson 29
//
#include "../../C.h"
#include <iostream>
#include <gtest/gtest.h>

namespace jsf2184 {


    template < typename T > class SP
    {
    private:
        T*    pData; // Generic pointer to be stored
    public:
        SP(T* pValue) : pData(pValue)
        {
        }
        ~SP()
        {
            delete pData;
        }

        T& operator* ()
        {
            return *pData;
        }

        T* operator-> ()
        {
            return pData;
        }
    };

    TEST(PointerWrapperTests, basicTest) {
        SP<C> sp(new C(3));
        EXPECT_EQ(3, sp->getX());
        C cCopy = *sp;
        EXPECT_EQ(3, cCopy.getX());
    }

}
