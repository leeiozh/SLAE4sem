//
// Created by kuznetsov on 04.02.2022.
//

#include "gtest/gtest.h"
#include <my_project/SlaeBaseException.hpp>

void throwException() { throw Slae::SlaeBaseExceptionCpp("Hi"); }

TEST(EXCEPTION, EXCEPTION_HI) {
    bool isCaught = false;
    try {
        throwException();
    } catch (const Slae::SlaeBaseExceptionCpp &err) {
        isCaught = true;
    }
    ASSERT_TRUE(isCaught);
}
