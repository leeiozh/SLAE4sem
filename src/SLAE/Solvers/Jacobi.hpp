//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_JACOBI_HPP
#define SLAE_JACOBI_HPP

#include "../Sparse/CSR.hpp"
#include "../Utility/Norm.hpp"

/**
 * функция, реализующая метод Якоби для решения СЛАУ
 * @tparam T шаблонный тип
 * @param A матрица системы
 * @param b свободный столбец системы
 * @param init_res начальнео приближение решения
 * @param tolerance точность, предъявляемая к результату
 * @return решение СЛАУ Ax = b в пределах tolarance
 * @throw SlaeBaseException если матрица не квадратная или какие-то размеры не совпадают
 */
template <typename T>
std::vector<T> Jacobi(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &init_res, const T &tolerance) {

#ifndef NDEBUG
    if (A.sizeH() != A.sizeW()) {
        std::stringstream buff;
        buff << "Matrix must be quadratic!" << std::endl;
        throw Slae::SlaeBaseException(buff.str());
    }
    if (A.sizeH() != b.size()) {
        std::stringstream buff;
        buff << "Matrix and free column must have be same size! A.size " << A.sizeH() << "! b.size << " << b.size()
             << "!" << std::endl;
        throw Slae::SlaeBaseException(buff.str());
    }
    if (init_res.size() != b.size()) {
        std::stringstream buff;
        buff << "InitState and free column must have be same size! init.size " << init_res.size() << "! b.size << "
             << b.size() << "!" << std::endl;
        throw Slae::SlaeBaseException(buff.str());
    }
#endif // NDEBUG

    std::vector<T> res = init_res;
    std::vector<T> x_tmp = init_res;
    T sum = static_cast<T>(0);

    // алгоритм описан в docs -> Системы уравнений. Лекция 2. Базовые методы.pdf стр. 29
    while (norm(A * res - b, NormType::ThirdNorm) > tolerance) {
        x_tmp = res;
        for (int i = 0; i < b.size(); ++i) {
            sum = static_cast<T>(0);
            int skip = 0;
            int count = 0;
            for (int k = skip; k < skip + count; ++k) {
                if (i != A.cols_[k]) sum += A.values_[k] * x_tmp[i];
                else continue;
            }
            res[i] = (b[i] - sum) / A(i, i);
        }
    }
    return res;
}

#endif//SLAE_JACOBI_HPP
