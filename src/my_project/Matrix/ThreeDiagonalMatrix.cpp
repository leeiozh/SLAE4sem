//
// Created by leeiozh on 05.02.2022.
//

#include "ThreeDiagonalMatrix.hpp"

namespace Slae::Matrix {

double &ThreeDiagonalMatrix::operator()(int i, int j) {
#ifndef NDEBUG
    if (i >= size_) {
        std::stringstream buff;
        buff << "Wrong index i! Index " << i << "! Size " << size_ << "!" << std::endl;
        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
    if (j > 2 || j < 0) {
        std::stringstream buff;
        buff << "Wrong index j! Index " << j << "!" << std::endl;
        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
#endif
    return matrix_[3 * i + j];
}

const double &ThreeDiagonalMatrix::operator()(int i, int j) const {
#ifndef NDEBUG
    if (i >= size_) {
        std::stringstream buff;
        buff << "Wrong index i! Index " << i << "! Size " << size_ << "!" << std::endl;
        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
    if (j > 2 || j < 0) {
        std::stringstream buff;
        buff << "Wrong index j! Index " << j << "!" << std::endl;
        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
#endif
    return matrix_[3 * i + j];
}

ThreeDiagonalMatrix ThreeDiagonalMatrix::Zero(int size) {
    ThreeDiagonalMatrix result(size);
    for (auto elem: result.matrix_) {
        elem = 0.;
    }
    return result;
}

} // namespace Slae::Matrix
