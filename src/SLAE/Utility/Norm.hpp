//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_NORM_HPP
#define SLAE_NORM_HPP

#include <vector>
#include <math.h>

enum class NormType {
    /**
     * класс реализации различных норм матриц
     */
    FirstNorm = 1, // максимальный по модулю элемент
    SecondNorm = 2, // сумма модулей всех элементов
    ThirdNorm = 3, // корень суммы квадартов всех элементов
};

template <typename T>
T norm(const std::vector<T> &vec, NormType type) {
    T res = static_cast<T>(0);
    if (type == NormType::FirstNorm) {
        // первая норма это максимальный по модулю элемент
        for (const auto &el: vec) {
            res = std::max(res, std::abs(el));
        }
        return res;
    }
    if (type == NormType::SecondNorm) {
        // вторая норма это сумма модулей всех элементов
        for (const auto &el: vec) {
            res += std::abs(el);
        }
        return res;
    }
    if (type == NormType::ThirdNorm) {
        // третья норма это корень суммы квадартов всех элементов
        for (const auto &el: vec) {
            res += el * el;
        }
        return std::sqrt(res);
    }
    return res;
}

#endif//SLAE_NORM_HPP
