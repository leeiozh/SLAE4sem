//
// Created by leeiozh on 20.06.22.
//

#include "gtest/gtest.h"
#include <SLAE/SlaeBaseException.hpp>
#include <SLAE/Matrix/DenseMatrix.hpp>
#include <SLAE/Sparse/CSR.hpp>
#include <SLAE/Utility/Triplet.hpp>
#include <SLAE/Utility/Overloads.hpp>
#include "SLAE/Utility/Number.hpp"
#include <SLAE/Solvers/GaussClassic.hpp>

//TEST(DENSE_SIMPLE, CON_NUM_2) {
//
//    float obusl = 2000;
//    float coeff = 0.01;
//
//    for (int size = 4; size < 1e6; size *= 2) {
//
//        std::set<Triplet<float>> my_triplets;
//        std::vector<float> b_col(size);
//
//        for (int i = 0; i < size; i++) {
//            for (int j = 0; j < size; j++) {
//                float num = static_cast<float>(1 + i + coeff * j) / size * obusl;
//                my_triplets.insert(Triplet<float>{static_cast<size_t>(i), static_cast<size_t>(j), num});
//            }
//            b_col[i] = 1;
//        }
//
//        DenseMatrix<float> my_dense = DenseMatrix<float>(size, size, my_triplets);
//
//        size_t solution = GaussMethod(my_dense, b_col);
//
//        std::cout << size << " " << solution << std::endl;
//    }
//}


TEST(DENSE_SIMPLE, CON_NUM_) {

    float obusl = 2;

    for (int size = 2; size < 1e6; size *= 2) {

        std::set<Triplet<Number<float>>> my_triplets;
        std::vector<Number<float>> b_col(size);

        auto orto = makeOrtoMatrix<Number<float>>(size);
        auto orto_trans = transpose(orto);

        for (int i = 0; i < size; i++) {
            my_triplets.insert(Triplet<Number<float>>{static_cast<size_t>(i), static_cast<size_t>(i), {i / size * obusl, 0}});
            b_col[i].value = size / (i + 1);
            b_col[i].count_oper = 0;
        }

        std::cout << size << " ";

        DenseMatrix<Number<float>> my_dense = DenseMatrix<Number<float>>(size, size, my_triplets);

        auto matr = orto_trans * my_dense * orto;

        std::vector<float> solution = headGaussMethod(my_dense, b_col);

        float ans = 0;
        for (int i = 0; i < size; i++) {
            float sun = 0;
            for (int j = 0; j < size; j++) {
                sun += my_dense(i, j) * solution[j];
            }
            ans += (sun - b_col[i]) * (sun - b_col[i]);
        }
        ans = std::sqrt(ans);

        std::cout << ans << std::endl;
    }
}

//TEST(DENSE_SIMPLE, TMP) {
//    float obusl = 20;
//    float coeff = 0.01;
//
//    int size = 5;
//
//    std::set<Triplet<float>> my_triplets;
//    std::vector<float> b_col(size);
//    b_col[0] = 2;
//    b_col[1] = 1;
//    b_col[2] = 2;
//
//    my_triplets.insert(Triplet<float>{0, 0, 1});
//    my_triplets.insert(Triplet<float>{0, 1, 1});
//    my_triplets.insert(Triplet<float>{1, 1, 1});
//    my_triplets.insert(Triplet<float>{2, 2, 1});
//    my_triplets.insert(Triplet<float>{3, 3, 1});
//    my_triplets.insert(Triplet<float>{4, 4, 1});
//
//    std::cout << size << " ";
//
//    DenseMatrix<float> my_dense = DenseMatrix<float>(size, size, my_triplets);
//
//    std::vector<float> solution = GaussMethod(my_dense, b_col);
//
//    float ans = 0;
//    for (int i = 0; i < size; i++) {
//        float sun = 0;
//        for (int j = 0; j < size; j++) {
//            sun += my_dense(i, j) * solution[i];
//        }
//        ans += (sun - b_col[i]) * (sun - b_col[i]);
//    }
//    ans = std::sqrt(ans);
//
//    std::cout << ans << std::endl;
//    std::cout << solution << std::endl;
//}