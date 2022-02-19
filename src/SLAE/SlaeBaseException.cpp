//
// Created by kuznetsov on 04.02.2022.
//

#include "SlaeBaseException.hpp"

namespace Slae {

SlaeBaseException::SlaeBaseException(const char *message) noexcept
    : message_(message) {}

SlaeBaseException::SlaeBaseException(const std::string &message) noexcept
    : SlaeBaseException(message.c_str()) {}

const char *SlaeBaseException::what() const noexcept { return message_.c_str(); }
} // namespace Slae
