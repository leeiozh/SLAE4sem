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
private:
    int size_ = 0;
    std::vector<double> matrix_;

public:
    inline explicit ThreeDiagonalMatrix(int size) : size_(size), matrix_(std::vector<double>(3 * size)) {};

    static ThreeDiagonalMatrix Zero(int size);

    [[nodiscard]] int size() const noexcept {
        return size_;
    }

    double &operator()(int i, int j);

    const double &operator()(int i, int j) const;

};
} // namespace Slae::Matrix



#endif //MY_PROJECT_THREEDIAGONALMATRIX_HPP
