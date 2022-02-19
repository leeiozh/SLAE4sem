//
// Created by leeiozh on 12.02.2022.
//
#include "gtest/gtest.h"
#include <SLAE/SlaeBaseException.hpp>
#include <SLAE/Sparse/CSR.hpp>
#include <SLAE/Utility/Triplet.hpp>
#include <SLAE/Utility/Overloads.hpp>

TEST(CSR_SIMPLE, CONSTRUCT) {

    // тест на корректное создание и заполнение

    std::set<Triplet<int>> my_triplets;
    my_triplets.insert(Triplet<int>{0, 0, 20});
    CSR<int> my_csr = CSR<int>(4, 4, my_triplets);

    ASSERT_TRUE(my_csr(0, 0) == 20);
    ASSERT_TRUE(my_csr(1, 1) == 0);

    bool isCaught = false;
    try {
        auto tmp = my_csr(10, 10);
    } catch (const Slae::SlaeBaseException &err) {
        isCaught = true;
    }
    ASSERT_TRUE(isCaught);
}

TEST(CSR_SIMPLE, PRODUCT_VEC) {

    // тест на корректное умножение матрицы на вектор

    std::set<Triplet<int>> my_triplets;
    my_triplets.insert(Triplet<int>{0, 0, 20});
    my_triplets.insert(Triplet<int>{1, 1, 3});
    CSR<int> my_csr = CSR<int>(4, 2, my_triplets);

    std::vector<int> vec({5, 2});
    auto res = my_csr * vec;

    ASSERT_TRUE(res[0] == 100);

    bool isCaught = false;
    try {
        vec.push_back(45);
        auto tmp = my_csr * vec;
    } catch (const Slae::SlaeBaseException &err) {
        isCaught = true;
    }
    ASSERT_TRUE(isCaught);
}
