//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_SIMPLEITERATION_HPP
#define SLAE_SIMPLEITERATION_HPP

#include "../Sparse/CSR.hpp"
#include "../Utility/Norm.hpp"

/**
 * функция, реализующая метод простой итерации для решения СЛАУ
 * @tparam T шаблонный тип
 * @param A матрица системы
 * @param b свободный столбец системы
 * @param init начальнео приближение решения
 * @param tolerance точность, предъявляемая к результату
 * @return решение СЛАУ Ax = b в пределах tolarance
 * @throw SlaeBaseException если матрица не квадратная или какие-то размеры не совпадают
 */
template <typename T>
std::vector<T> SimpleIteration(const CSR<T> &A, const std::vector<T> &b, const std::vector<T> &init, const T &tolerance,
                               const T &tao) {
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
    if (init.size() != b.size()) {
        std::stringstream buff;
        buff << "InitState and free column must have be same size! init.size " << init.size() << "! b.size << "
             << b.size() << "!" << std::endl;
        throw Slae::SlaeBaseException(buff.str());
    }
    std::vector<T> res = init;
    std::vector<T> r = A * res - b;

    // алгоритм описан в docs -> Системы уравнений. Лекция 2. Базовые методы.pdf стр. 31
    while (norm(r, NormType::ThirdNorm) > tolerance) {
        res = res - tao * r;
        r = A * res - b;
    }
    return res;
#endif // NDEBUG
}

#endif//SLAE_SIMPLEITERATION_HPP
