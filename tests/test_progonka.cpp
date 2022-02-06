//
// Created by leeiozh on 05.02.2022.
//

#include "gtest/gtest.h"
#include <my_project/SlaeBaseException.hpp>
#include <my_project/Matrix/ThreeDiagonalMatrix.hpp>
#include <my_project/Solvers/ThreeDiagonalMatrixSolver.hpp>

TEST(MATRIX_THREE, CONSTRUCT_ZERO) {

    Slae::Matrix::ThreeDiagonalMatrix my_matr = Slae::Matrix::ThreeDiagonalMatrix::Zero(5);

    ASSERT_TRUE(my_matr(0, 0) == 0.);
}

TEST(MATRIX_THREE, EXCEPTION) {

    Slae::Matrix::ThreeDiagonalMatrix my_matr(5);
    bool isCaught = true;
    try {
        my_matr(0, 0);
    } catch (const Slae::SlaeBaseExceptionCpp &err) {
        isCaught = false;
    }

    ASSERT_TRUE(isCaught);
}

TEST(MATRIX_THREE, SOLVE_SIMPLE) {
    Slae::Matrix::ThreeDiagonalMatrix my_matr = Slae::Matrix::ThreeDiagonalMatrix::Zero(3);

    my_matr(0, 0) = 5.;
    my_matr(1, 0) = 1.;
    my_matr(0, 1) = 1.;
    my_matr(1, 1) = 6;
    my_matr(2, 1) = 1.;
    my_matr(1, 2) = 1.;
    my_matr(2, 2) = 10.;

    std::vector<double> col(3);
    col[0] = 57.;
    col[1] = 57.;
    col[2] = 57.;

    std::vector<double> res;
    res = Slae::Solvers::solveThreeDiagonal(my_matr, col);

    ASSERT_NEAR(res[0], 10., 1e-15);
    ASSERT_NEAR(res[1], 7., 1e-15);
    ASSERT_NEAR(res[2], 5., 1e-15);
}
