//
// Created by petrov on 12.02.2022.
//

#ifndef SLAE_TRIPLET_HPP
#define SLAE_TRIPLET_HPP

#include <cstdio>

template <typename T>
struct Triplet {
    /**
     * структура триплет для описания единичного элемента матрицы
     */
    std::size_t i; // строка элемента
    std::size_t j; // столбец эелемента
    T value; // значение элемента

    // оператор сравнения триплетов, возвращает элемент, который выше и левее по матрице
    bool operator<(Triplet<T> const &rgh) const {
        return this->i < rgh.i || this->i == rgh.i && this->j < rgh.j;
    };
};

#endif//SLAE_TRIPLET_HPP
