//
// Created by leeiozh on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALMATRIX_HPP
#define MY_PROJECT_THREEDIAGONALMATRIX_HPP

#include "../SlaeBaseException.hpp"
#include <array>
#include <vector>

namespace Slae::Matrix {
class ThreeDiagonalMatrix {
    /**
     * class for three diagonal quadratic matrix
     */
private:
    int size_ = 0; // size for quadratic matrix
    std::vector<double> matrix_; // data of matrix coefficients

public:
    /**
     * constructor for three diagonal quadratic matrix
     * @param size number of columns/rows
     */
    inline explicit ThreeDiagonalMatrix(int size) : size_(size), matrix_(std::vector<double>(3 * size)) {};

    /**
     * manufacture for zero quadratic matrix
     * @param size number of columns/rows
     * @return zero quadratic matrix with *size* columns/rows
     */
    static ThreeDiagonalMatrix Zero(int size);

    /**
     * getter for size field
     * @return size of matrix
     */
    [[nodiscard]] int size() const noexcept {
        return size_;
    }

    /**
     * operator for connections with (i, j) elements
     * @param i number of row
     * @param j number of column
     * @return (i, j) element
     * @throw SlaeBaseException when i >= size, j not in {0, 1, 2}
     */
    double &operator()(int i, int j);

    /**
     * const operator for connections with (i, j) elements
     * @param i number of row
     * @param j number of column
     * @return (i, j) element
     * @throw SlaeBaseException when i >= size, j not in {0, 1, 2}
     */
    [[nodiscard]] const double &operator()(int i, int j) const;

};
} // namespace Slae::Matrix



#endif //MY_PROJECT_THREEDIAGONALMATRIX_HPP
