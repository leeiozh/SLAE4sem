//
// Created by leeiozh on 12.02.2022.
//
#include "gtest/gtest.h"
#include <SLAE/SlaeBaseException.hpp>
#include <SLAE/Matrix/DenseMatrix.hpp>
#include <SLAE/Sparse/CSR.hpp>
#include <SLAE/Utility/Triplet.hpp>
#include <SLAE/Utility/Overloads.hpp>


TEST(DENSE_SIMPLE, CONSTRUCT) {

    // тест на корректное создание плотной матрицы

    std::set<Triplet<int>> my_triplets;
    my_triplets.insert(Triplet<int>{0, 0, 20});
    my_triplets.insert(Triplet<int>{1, 1, 5});
    my_triplets.insert(Triplet<int>{2, 0, 4});
    my_triplets.insert(Triplet<int>{0, 3, -10});
    DenseMatrix<int> my_dense = DenseMatrix<int>(4, 4, my_triplets);

    ASSERT_TRUE(my_dense(0, 0) == 20);
    ASSERT_TRUE(my_dense(1, 1) == 5);

    my_dense(1, 1) = 8;

    ASSERT_TRUE(my_dense(1, 1) == 8);

    bool isCaught = false;
    try {
        auto tmp = my_dense(10, 10);
    } catch (const Slae::SlaeBaseExceptionCpp &err) {
        isCaught = true;
    }
    ASSERT_TRUE(isCaught);
}