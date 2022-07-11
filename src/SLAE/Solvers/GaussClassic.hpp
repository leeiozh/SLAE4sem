//
// Created by leeiozh on 20.06.22.
//

#ifndef SLAE_GAUSSCLASSIC_HPP
#define SLAE_GAUSSCLASSIC_HPP

#include "../Matrix/DenseMatrix.hpp"
#include "../Utility/Consts.hpp"

template <typename T>
typename DenseMatrix<T>::idx_t col_nonzero(const DenseMatrix<T> &A, const typename DenseMatrix<T>::idx_t &col) {
    using idx_t = typename DenseMatrix<T>::idx_t;
    if (Tabs(A(col, col)) > tolerance<T>) return col;
    else {
        for (idx_t i = col + 1; i < A.sizeH(); ++i) {
            if (Tabs(A(i, col)) > tolerance<T>) return i;
        }
    }
    return col;
}

template <typename T>
typename DenseMatrix<T>::idx_t col_max(const DenseMatrix<T> &A, const typename DenseMatrix<T>::idx_t &col) {
    using idx_t = typename DenseMatrix<T>::idx_t;
    using elm_t = typename DenseMatrix<T>::elm_t;
    elm_t max = Tabs(A(col, col));
    int maxPos = col;
    for (idx_t i = col + 1; i < A.sizeH(); ++i) {     //поиск максимального по модулю элемента в столбце col
        elm_t element = Tabs(A(i, col));
        if (element > max) {
            max = element;
            maxPos = i;
        }
    }
    return maxPos;
}

template <typename T>
T triangulation(DenseMatrix<T> &A, std::vector<T> &b) {
    using idx_t = typename DenseMatrix<T>::idx_t;
    using elm_t = typename DenseMatrix<T>::elm_t;

    std::size_t oper_count = 0;

    for (idx_t i = 0; i < A.sizeH() - 1; ++i) {
        idx_t iNonZero = col_nonzero(A, i);
        ++oper_count;
        if (Tabs(A(iNonZero, i)) > tolerance<T>) {
            A.swap(i, iNonZero);
            std::swap(b[i], b[iNonZero]);
            ++oper_count;
        } else { continue; }
        for (idx_t k = i + 1; k < A.sizeH(); ++k) {
            elm_t coef = A(k, i) / A(i, i);
            for (idx_t j = 0; j < A.sizeW(); ++j) {
                A(k, j) -= A(i, j) * coef;
                ++oper_count;
            }
            b[k] -= b[i] * coef;
        }
    }
    return oper_count;
}

template<typename T>
std::vector<T> backSubstTopTriangular(const DenseMatrix<T>& A, const std::vector<T>& b){
    float oper_count = 0;
    std::vector<T> res(b.size());
    res.back() = b.back()/A(A.sizeH()-1, A.sizeW()-1);
    T sum;
    for(int i = b.size() - 2; i >= 0; --i){
        sum = 0;
        for(size_t j = i + 1; j < b.size(); ++j){
            sum += A(i, j) * res[j];
            oper_count ++;
        }
        res[i] = (b[i] - sum) / A(i, i);
    }
    std::cout << oper_count << " ";
    return res;
}

template <typename T>
T headTriangulation(DenseMatrix<T> &A, std::vector<T> &b) {

    using idx_t = typename DenseMatrix<T>::idx_t;
    using elm_t = typename DenseMatrix<T>::elm_t;

    T oper_count = 0;

    for (idx_t i = 0; i < A.sizeH() - 1; ++i) {
        idx_t imax = col_max(A, i); //индекс максимального по модулю элемента под диагональю
        if (Tabs(A(imax, i)) < tolerance<T>) {  //если максимальный равен 0, то пропускаем столбец из рассмотрения
            continue;
        } else {
            if (i != imax) {
                A.swap(i, imax);        //переставляем строку с максимальным по модулю элементом с текущей местами
                std::swap(b[i], b[imax]); //элемент свободного столбца также переставляется
            }

            for (idx_t k = i + 1; k < A.sizeH(); ++k) { //проход по всем строкам под текущей
                ++oper_count;
                elm_t coef = (A(k, i) / A(i, i));
                for (idx_t j = i; j < A.sizeW(); ++j) { //проход по всем элементам строки
                    A(k, j) -= A(i, j) *
                               coef;          //вычитание из строки k строки i, умноженной на коэффициент для зануления элементов столбца i
                }
                b[k] -= b[i] * coef; //вычитание свободного члена уравнения
            }
        }
    }
    return oper_count;   //возвращаем число перестановок(может потребоваться для поиска определителя)
}

template <typename T>
std::vector<T> backSubstTopTriangular(const DenseMatrix<T> &A, const std::vector<T> &b, size_t SZ) {
    T oper_count = 0;
    std::vector<T> res(b.size());
    res.back() = b.back() / A(SZ - 1, SZ - 1);
    T sum;
    for (int i = int(SZ) - 2; i >= 0; --i) {
        sum = 0;
        for (size_t j = i + 1; j < b.size(); ++j) {
            sum += A(i, j) * res[j];
            ++oper_count;
        }
        res[i] = (b[i] - sum) / A(i, i);
    }
    std::cout << oper_count << " ";
    return res;
}

template <typename T>
T backSubstLowerTriangular(const DenseMatrix<T> &A, const std::vector<T> &b) {
    std::vector<T> res(b.size());
    res[0] = b[0] / A(0, 0);
    T sum;
    for (int i = 1; i < A.sizeH(); ++i) {
        sum = 0;
        for (int j = 0; j < i; ++j) {
            sum += A(i, j) * res[j];
        }
        res[i] = (b[i] - sum) / A(i, i);
    }
    return res;
}

template <typename T>
std::vector<T> GaussMethod(DenseMatrix<T> A, std::vector<T> b) {
    T num = triangulation(A, b);
    std::cout << num << " ";
    return backSubstTopTriangular(A, b);
}

template <typename T>
std::vector<T> headGaussMethod(DenseMatrix<T> A,
                               std::vector<T> b) {

    T oper_count = headTriangulation(A, b); //приводим матрицу к верхнетреугольной с выбором главного элемента
    std::cout << oper_count << " ";
    return backSubstTopTriangular(A, b);
}

#endif //SLAE_GAUSSCLASSIC_HPP
