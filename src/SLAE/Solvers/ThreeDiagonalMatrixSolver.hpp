//
// Created by leeiozh on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALMATRIXSOLVER_HPP
#define MY_PROJECT_THREEDIAGONALMATRIXSOLVER_HPP

#include "SLAE/Matrix/ThreeDiagonalMatrix.hpp"
#include "SLAE/SlaeBaseException.hpp"
#include <sstream>

namespace Slae::Solvers {

std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix &matrix, const std::vector<double> &col);

} // namespace Slae::Solvers

#endif //MY_PROJECT_THREEDIAGONALMATRIXSOLVER_HPP
