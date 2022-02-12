//
// Created by petrov on 12.02.2022.
//

#ifndef SOLE2022_CSR_HPP
#define SOLE2022_CSR_HPP

#include <vector>
#include <set>
#include <iostream>
#include "../SlaeBaseException.hpp"
#include "../Utility/Triplet.hpp"

template <typename T>
class CSR {
public:
    using elm_t = T;          // Тип данных элементов матрицы
    using idx_t = std::size_t;// Тип индекса

private:
    const idx_t H_, W_;         //Размеры матрицы
    std::vector<elm_t> values_; //Вектор значений (размер N - кол-во ненулевых элементов)
    std::vector<idx_t> cols_;  // Вектор номеров столбцов, соответствующих значениям (размер N - кол-во ненулевых элементов)
    std::vector<idx_t> rows_;  // Вектор индексации строк размера H+1, первый элемент = 0 в качестве запирающего

public:
    /***
     * Конструктор разреженной матрицы по готовым векторам с внутренней структурой
     * @param h число строк
     * @param w число столбцов
     * @param v вектор ненулевых значений
     * @param c вектор индексации столбцов
     * @param r вектор индексации строк
     */
    CSR(const idx_t &h, const idx_t &w, const std::vector<T> &v, const std::vector<T> &c, const std::vector<T> &r) : H_(
            h), W_(w), values_(std::move(v)), cols_(std::move(c)), rows_(std::move(r)) {};

    /***
     * Конструктор разреженной матрицы по сету из Triplet
     * @param h число строк
     * @param w число столбцов
     */
    CSR(const idx_t &h, const idx_t &w, const std::set<Triplet<elm_t>> &in) : H_(h), W_(w) {
        values_.resize(in.size());
        cols_.resize(in.size());
        rows_.resize(h + 1);
        int countInRow = 0;
        int currRow = 0;
        auto it = in.begin();
        for (idx_t k = 0; k < in.size(); ++k) {
            while (currRow < it->i) {
                rows_[currRow + 1] = rows_[currRow] + countInRow;
                ++currRow;
                countInRow = 0;
            }
            values_[k] = it->value;
            cols_[k] = it->j;
            ++countInRow;
            it = next(it);
        }
        for (++currRow; currRow <= H_; ++currRow) {
            rows_[currRow] = in.size();
        }
    };

    /***
     * Оператор получения элемента матрицы по индексам
     * @param i Номер строки
     * @param j Номер столбца
     * @return Значение элемента в позиции (i, j)
     * @throw SlaeExceprtion if i > H_size or j > W_size
     */
    const elm_t operator()(idx_t const i, idx_t const j) const {

#ifndef NDEBUG
        if (i > H_ || i < 0) {
            std::stringstream buff;
            buff << "Index more H size! H size " << H_ << "! Index " << i << "!" << std::endl;
            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
        if (j > W_ || j < 0) {
            std::stringstream buff;
            buff << "Index more W size! W size " << W_ << "! Index " << j << "!" << std::endl;
            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif //NDEBUG

        idx_t skip = this->rows_[i];
        idx_t count = this->rows_[i + 1] - skip;
        for (idx_t k = skip; k < skip + count; ++k) {
            if (this->cols_[k] == j) return this->values_[k];
        }
        return static_cast<elm_t>(0);
    }

    /***
     * Оператор умножения матрицы на вектор
     * @param b Вектор, на который умножается матрица
     * @return Вектор - результат перемножения
     */
    std::vector<elm_t> operator*(const std::vector<elm_t> &b) const {
#ifndef NDEBUG
        if (b.size() != W_) {
            std::stringstream buff;
            buff << "b and matrix nust have same size! b_size " << b.size() << "! H_size " << H_ << "!" << std::endl;
            throw Slae::SlaeBaseExceptionCpp(buff.str());
        }
#endif // NDEBUG
        std::vector<elm_t> res(this->H_);
        for (idx_t i = 0; i < H_; ++i) {
            for (idx_t j = rows_[i]; j < rows_[i + 1]; ++j) res[i] += values_[j] * b[cols_[j]];
        }
        return res;
    };

    /**
     * @return количество строк в матрице
     */
    [[nodiscard]] idx_t sizeH() const {
        return H_;
    }

    /**
     * @return количество столбцов в матрице
     */
    idx_t sizeW() const {
        return W_;
    }
};

/**
 * Оператор вывода матрицы в поток
 * @tparam T - используемый тип данных
 * @param os - поток вывода
 * @param A - матрица CSR
 * @return поток с матрицей
 */
template <typename T>
std::ostream &operator<<(std::ostream &os, const CSR<T> &A) {
    os << std::endl;
    for (std::size_t i = 0; i < A.sizeH(); ++i) {
        for (std::size_t j = 0; j < A.sizeW(); ++j) {
            os << A(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
};

#endif//SOLE2022_CSR_HPP
