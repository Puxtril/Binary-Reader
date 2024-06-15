#pragma once

#include <exception>
#include <stdexcept>
#include <sstream>
#include <cstdint>
#include <string>
#include <concepts>

class LimitException : public std::runtime_error
{
public:
    const size_t index;

    LimitException(const auto& value, const auto& limit, const std::string& msg)
        : runtime_error("Limit hit. \"" + msg + "\""), index(0)
    {}

    LimitException(const auto& value, const auto& limit, size_t index, const std::string& msg)
        : runtime_error("Limit hit at index " + std::to_string(index) + ". \"" + msg + "\""), index(index)
    {}
};

class NonNormalFloatException : public std::runtime_error
{
public:
    template <typename T>
    NonNormalFloatException(const T& value, const std::string& msg)
        : runtime_error("Non-Normal float read: (" + std::to_string(value) + ") \"" + msg + "\"")
    {}
};
