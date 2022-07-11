//
// Created by leeiozh on 23.06.22.
//

#ifndef SLAE_NUMBER_HPP
#define SLAE_NUMBER_HPP

template <typename T>
struct Number {
    T value;
    int count_oper = 0;

    bool operator<(Number<T> const &rgh) const {
        return value < rgh.value;
    };

    bool operator==(Number<T> const &rgh) const {
        return value == rgh.value;
    }

    Number operator+(Number<T> const &rgh) const {
        return {value + rgh.value, count_oper + rgh.count_oper};
    }

    Number operator*(Number<T> const &rgh) const {
        return {value * rgh.value, count_oper + rgh.count_oper};
    }

    Number operator+(T const &rgh) const {
        return {value + rgh, count_oper + 1};
    }

    Number operator*(T const &rgh) const {
        return {value * rgh, count_oper + 1};
    }

    Number operator-(Number<T> const &rgh) const {
        return this + (-1) * rgh;
    }

    Number operator-(T const &rgh) const {
        return {value - rgh, count_oper + 1};
    }

    Number operator/(Number<T> const &rgh) const {
        return {value / rgh.value, count_oper + rgh.count_oper};
    }

    Number operator/(T const &rgh) const {
        return {value / rgh, count_oper + 1};
    }
};

#endif //SLAE_NUMBER_HPP
