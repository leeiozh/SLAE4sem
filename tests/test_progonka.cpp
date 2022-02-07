//
// Created by leeiozh on 05.02.2022.
//

#include "gtest/gtest.h"
#include <SLAE/SlaeBaseException.hpp>
#include <SLAE/Matrix/ThreeDiagonalMatrix.hpp>
#include <SLAE/Solvers/ThreeDiagonalMatrixSolver.hpp>

TEST(MATRIX_THREE, CONSTRUCT_ZERO) {
    // тест на корректное создание нулевой матрицы

    int size = 50;
    Slae::Matrix::ThreeDiagonalMatrix my_matr = Slae::Matrix::ThreeDiagonalMatrix::Zero(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_TRUE(my_matr(i, j) == 0.);
        }
    }
}

TEST(MATRIX_THREE, EXCEPTION_I) {
    // тест на отбработку исключения для неверного индекса i

    Slae::Matrix::ThreeDiagonalMatrix my_matr(5);
    bool isCaught = false;
    try {
        my_matr(7, 0);
    } catch (const Slae::SlaeBaseExceptionCpp &err) {
        isCaught = true;
    }
    ASSERT_TRUE(isCaught);
}

TEST(MATRIX_THREE, EXCEPTION_J) {
    // тест на отбработку исключения для неверного индекса j

    Slae::Matrix::ThreeDiagonalMatrix my_matr(5);
    bool isCaught = false;
    try {
        my_matr(0, 5);
    } catch (const Slae::SlaeBaseExceptionCpp &err) {
        isCaught = true;
    }
    ASSERT_TRUE(isCaught);
}

TEST(MATRIX_THREE, SOLVE_SIMPLE) {
    // тест на решение простой системы

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

TEST(MATRIX_THREE, SOLVE_MEDIUM) {
    // тест на решение непростой системы

    int size = 10;
    double tolerance = 1.e-10;
    Slae::Matrix::ThreeDiagonalMatrix my_matr = Slae::Matrix::ThreeDiagonalMatrix::Zero(size);
    std::vector<double> col(size);

    for (int i = 0; i < size; ++i) {
        my_matr(i, 0) = 1.;
        my_matr(i, 1) = 10.;
        my_matr(i, 2) = 2.;
        col[i] = 1.;
    }

    my_matr(0, 1) = 60.;
    my_matr(size - 1, 1) = 5.;

    std::vector<double> res;
    res = Slae::Solvers::solveThreeDiagonal(my_matr, col);

    ASSERT_NEAR(res[0], 0.7973820394, tolerance);
    ASSERT_NEAR(res[1], 0.003376966009, tolerance);
    ASSERT_NEAR(res[2], 0.08442415023, tolerance);
    ASSERT_NEAR(res[3], 0.07619076585, tolerance);
    ASSERT_NEAR(res[4], 0.07683409566, tolerance);
    ASSERT_NEAR(res[5], 0.0777341388, tolerance);
    ASSERT_NEAR(res[6], 0.07291225816, tolerance);
    ASSERT_NEAR(res[7], 0.09657163977, tolerance);
    ASSERT_NEAR(res[8], -0.01931432795, tolerance);
    ASSERT_NEAR(res[9], 0.5482858199, tolerance);
}

TEST(MATRIX_THREE, SOLVE_HARD) {
    // тест на решение самой сложной системы в моей жизни

    int size = 100;
    double tolerance = 2.e-5;
    Slae::Matrix::ThreeDiagonalMatrix my_matr = Slae::Matrix::ThreeDiagonalMatrix::Zero(size);
    std::vector<double> col(size);

    for (int i = 0; i < size; ++i) {
        my_matr(i, 0) = 1.e-5;
        my_matr(i, 2) = 1.e-5;
        my_matr(i, 1) = 2.;
        col[i] = 4.;
    }
    my_matr(0, 1) = 60.;

    std::vector<double> res;
    res = Slae::Solvers::solveThreeDiagonal(my_matr, col);

    for (int i = 3; i < size - 3; ++i) {
        std::cout << std::setprecision(10) << res[i] << std::endl;
        ASSERT_NEAR(res[i], 1.99998, tolerance);
    }
}
