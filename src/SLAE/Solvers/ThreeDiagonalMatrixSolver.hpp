//
// Created by leeiozh on 05.02.2022.
//

#ifndef SLAE_THREEDIAGONALMATRIXSOLVER_HPP
#define SLAE_THREEDIAGONALMATRIXSOLVER_HPP

#include "SLAE/Matrix/ThreeDiagonalMatrix.hpp"
#include "SLAE/SlaeBaseException.hpp"
#include <sstream>

namespace Slae::Solvers {

/**
 * solver for three diagonal matrix by progonka method
 * @param matrix three diagonal matrix
 * @param col vector of free coefficients
 * @return vector of solutions
 * @throw SlaeBaseException when size matrix != size col
 */
[[nodiscard]] std::vector<double>
solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix &matrix, const std::vector<double> &col);

} // namespace Slae::Solvers

#endif //SLAE_THREEDIAGONALMATRIXSOLVER_HPP
