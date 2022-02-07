//
// Created by leeiozh on 05.02.2022.
//

#include "ThreeDiagonalMatrix.hpp"

namespace Slae::Matrix {

double &ThreeDiagonalMatrix::operator()(int i, int j) {
#ifndef NDEBUG
    if (i >= size_) {
        // исключение срабатывает в случае обращения к строке, превышающей размер матрицы
        std::stringstream buff;
        buff << "Wrong index i! Index " << i << "! Size " << size_ << "!" << std::endl;
        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
    if (j > 2 || j < 0) {
        // исключение срабатывает в случае обращения к элементу, не находящемуся на главной и соседних диагоналях
        std::stringstream buff;
        buff << "Wrong index j! Index " << j << "!" << std::endl;
        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
#endif
    // матрица хранится одним большим вектором по 3 значения из каждой строки подряд
    return matrix_[3 * i + j];
}

const double &ThreeDiagonalMatrix::operator()(int i, int j) const {
#ifndef NDEBUG
    if (i >= size_) {
        // исключение срабатывает в случае обращения к строке, превышающей размер матрицы
        std::stringstream buff;
        buff << "Wrong index i! Index " << i << "! Size " << size_ << "!" << std::endl;
        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
    if (j > 2 || j < 0) {
        // исключение срабатывает в случае обращения к элементу, не находящемуся на главной и соседних диагоналях
        std::stringstream buff;
        buff << "Wrong index j! Index " << j << "!" << std::endl;
        throw Slae::SlaeBaseExceptionCpp(buff.str());
    }
#endif
    // матрица хранится одним большим вектором по 3 значения из каждой строки подряд
    return matrix_[3 * i + j];
}

ThreeDiagonalMatrix ThreeDiagonalMatrix::Zero(int size) {
    // фабрика для создания нулевой матрицы размера size
    ThreeDiagonalMatrix result(size);
    result.matrix_ = std::vector<double>(3 * size, 0.);
    return result;
}

} // namespace Slae::Matrix
