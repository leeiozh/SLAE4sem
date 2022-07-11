//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_DENSEMATRIX_HPP
#define SLAE_DENSEMATRIX_HPP

#include <vector>
#include <set>
#include "cmath"
#include "SLAE/SlaeBaseException.hpp"
#include "SLAE/Utility/Triplet.hpp"

template <typename T>
class DenseMatrix {
    /*
     * класс плотнозаполненных матриц
     */
public:
    using elm_t = T; // тип данных
    using idx_t = std::size_t; // тип данных счетчиков

private:

    std::vector<T> matrix_; // вектор значений элементов матрицы считанных построчно
    idx_t H_, W_; // количество строк и столбцов в матрице

public:
    /**
     * конструктор пустой (нулевой) плотной матрицы
     * @param h количество строк
     * @param w количество столбцов
     */
    DenseMatrix(const idx_t &h, const idx_t &w) : H_(h), W_(w), matrix_(std::vector<elm_t>(h * w)) {};

    /**
     * конструктор плотной матрицы по сету триплетов
     * @param h количество строк
     * @param w количество столбцов
     * @param in сет триплетов с данными
     */
    DenseMatrix(const idx_t &h, const idx_t &w, const std::set<Triplet<T>> &in) : H_(h), W_(w),
                                                                                  matrix_(std::vector<elm_t>(h * w)) {
        for (auto &trip: in) {
            matrix_[trip.i * w + trip.j] = trip.value;
        }
    }

    /**
     * оператор обращения к (i, j) элементу
     * @param i строка
     * @param j столбец
     * @return ссылка на элемент
     * @throw SlaeBaseExceptionCpp if i > h_size or j > w_size
     */
    elm_t &operator()(const idx_t &i, const idx_t &j) {

#ifndef NDEBUG
        if (i >= H_ || i < 0) {
            std::stringstream buff;
            buff << "Index more H size! H size " << H_ << "! Index " << i << "!" << std::endl;
            throw Slae::SlaeBaseException(buff.str());
        }
        if (j >= W_ || j < 0) {
            std::stringstream buff;
            buff << "Index more W size! W size " << W_ << "! Index " << j << "!" << std::endl;
            throw Slae::SlaeBaseException(buff.str());
        }
#endif //NDEBUG

        return matrix_[i * W_ + j];
    };

    /**
     * оператор обращения к (i, j) элементу
     * @param i строка
     * @param j столбец
     * @return ссылка на элемент
     * @throw SlaeBaseExceptionCpp if i > h_size or j > w_size
     */
    [[nodiscard]] const elm_t &operator()(const idx_t &i, const idx_t &j) const {
#ifndef NDEBUG
        if (i >= H_ || i < 0) {
            std::stringstream buff;
            buff << "Index more H size! H size " << H_ << "! Index " << i << "!" << std::endl;
            throw Slae::SlaeBaseException(buff.str());
        }
        if (j >= W_ || j < 0) {
            std::stringstream buff;
            buff << "Index more W size! W size " << W_ << "! Index " << j << "!" << std::endl;
            throw Slae::SlaeBaseException(buff.str());
        }
#endif //NDEBUG

        return matrix_[i * W_ + j];
    }

    /**
     * @return количество строк в матрице
     */
    [[nodiscard]] const idx_t &sizeH() const {
        return H_;
    }

    /**
     * @return количество столбцов в матрице
     */
    [[nodiscard]] const idx_t &sizeW() const {
        return W_;
    }

    /**
     * функция перестановки двух строк
     * @param first первая строка
     * @param second вторая строка
     */
    void swap(const idx_t &first, const idx_t &second) {
        for (int i = 0; i < W_; ++i) {
            std::swap(matrix_[first * W_ + i], matrix_[second * W_ + i]);
        }
    }

    /**
     * функция удаления последней строки
     */
    void deleteLastRow() {
        H_--;
        matrix_.resize(H_ * W_);
    };

};

template <typename T>
DenseMatrix<T> makeOrtoMatrix(int size) {
    DenseMatrix<T> res(size, size);
    for (int i = 0; i < size; ++i) {
        std::srand(std::time(nullptr));
        T angle = static_cast <T> (rand()) / (static_cast <T> (RAND_MAX / 2 / M_PI));
        res(i, i) = std::cos(angle);
        res(size - 1 - i, i) = std::sin(angle);
        res(i, size - i - 1) = -std::sin(angle);
        res(size - i - 1, size - i - 1) = std::cos(angle);
    }
    return res;
}

template <typename T>
DenseMatrix<T> transpose(const DenseMatrix<T>& inp) {
    DenseMatrix<T> res(inp.sizeH(), inp.sizeW());
    for (int i = 0; i < inp.sizeH(); i++) {
        for (int j = 0; j < inp.sizeW(); j++) {
            res(i, j) = inp(j, i);
        }
    }
}

#endif//SLAE_DENSEMATRIX_HPP
