//
// Created by leeiozh on 19.02.2022.
//

#include "gtest/gtest.h"
#include <SLAE/SlaeBaseException.hpp>
#include <SLAE/Matrix/DenseMatrix.hpp>
#include <SLAE/Sparse/CSR.hpp>
#include <SLAE/Utility/Triplet.hpp>
#include <SLAE/Utility/Overloads.hpp>
#include <SLAE/Solvers/GaussSeidel.hpp>
#include <SLAE/Solvers/Jacobi.hpp>
#include <SLAE/Solvers/SimpleIteration.hpp>


TEST(GAUSS_ZEIDEL, SIMPLE) {

    double tol = 1e-10;
    std::set<Triplet<double>> my_triplets;
    my_triplets.insert(Triplet<double>{0, 0, 100});
    my_triplets.insert(Triplet<double>{1, 1, -100});
    my_triplets.insert(Triplet<double>{2, 2, 100});
    my_triplets.insert(Triplet<double>{0, 1, 0});
    CSR<double> my_csr = CSR<double>(3, 3, my_triplets);

    std::vector<double> col = {20, 10, 10};
    std::vector<double> init = {0, 0, 0};

    std::vector<double> res = GaussSeidel(my_csr, col, init, tol);
    ASSERT_NEAR(norm(res - std::vector<double>{0.2, -0.1, 0.1}, NormType::ThirdNorm), 0., tol);
}

TEST(JACOBI, SIMPLE) {
    double tol = 1e-10;
    std::set<Triplet<double>> my_triplets;
    my_triplets.insert(Triplet<double>{0, 0, 100});
    my_triplets.insert(Triplet<double>{1, 1, -100});
    my_triplets.insert(Triplet<double>{2, 2, 100});
    my_triplets.insert(Triplet<double>{0, 1, 0});
    CSR<double> my_csr = CSR<double>(3, 3, my_triplets);

    std::vector<double> col = {20, 10, 10};
    std::vector<double> init = {0, 0, 0};

    std::vector<double> res = Jacobi(my_csr, col, init, tol);
    ASSERT_NEAR(norm(res - std::vector<double>{0.2, -0.1, 0.1}, NormType::ThirdNorm), 0., tol);
}

TEST(SIMPLE_ITERATION, SIMPLE) {
    double tol = 1e-8;
    std::set<Triplet<double>> my_triplets;
    my_triplets.insert(Triplet<double>{0, 0, 0.1});
    my_triplets.insert(Triplet<double>{1, 1, 0.05});
    my_triplets.insert(Triplet<double>{2, 2, 0.1});
    CSR<double> my_csr = CSR<double>(3, 3, my_triplets);

    std::vector<double> col = {0.1, 0.2, 0.3};
    std::vector<double> init = {0., 0., 0.};

    std::vector<double> res = SimpleIteration(my_csr, col, init, tol, 0.15);
    ASSERT_NEAR(norm(res - std::vector<double>{1., 4., 3.}, NormType::ThirdNorm), 0., 1e2 * tol);
}