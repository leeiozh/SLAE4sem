//
// Created by leeiozh on 20.06.22.
//

#ifndef SLAE_CONSTS_HPP
#define SLAE_CONSTS_HPP

#include <cmath>
#include <vector>

template <typename T>
auto tolerance = static_cast<T>(1e-10);

template <typename T>
T Tabs(const T &a) {
    if (a < T(0)) return -a;
    else return a;
}

template <typename T>
T norm(const std::vector<T> &a) {
    T sum = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * a[i];
    }
    return sqrt(sum);
}

#endif //SLAE_CONSTS_HPP
