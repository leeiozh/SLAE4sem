//
// Created by kuznetsov on 04.02.2022.
//

#include "gtest/gtest.h"
#include <SLAE/SlaeBaseException.hpp>

void throwException() { throw Slae::SlaeBaseException("Hi"); }

TEST(EXCEPTION, EXCEPTION_HI) {
    bool isCaught = false;
    try {
        throwException();
    } catch (const Slae::SlaeBaseException &err) {
        isCaught = true;
    }
    ASSERT_TRUE(isCaught);
}
