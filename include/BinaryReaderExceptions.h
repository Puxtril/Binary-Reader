#pragma once

#include <exception>
#include <stdexcept>
#include <sstream>
#include <cstdint>
#include <string>

class LimitException : public std::runtime_error {
public:
    LimitException(uint64_t value, uint64_t limit, const std::string& msg)
        : runtime_error("Limit (" + std::to_string(limit) + ") hit: " + std::to_string(value) + " \"" + msg + "\"")
    {}

    LimitException(int64_t value, int64_t limit, const std::string& msg)
        : runtime_error("Limit (" + std::to_string(limit) + ") hit: " + std::to_string(value) + " \"" + msg + "\"")
    {}

    LimitException(double value, double limit, const std::string& msg)
        : runtime_error("Limit (" + std::to_string(limit) + ") hit: " + std::to_string(value) + " \"" + msg + "\"")
    {}
};

class NonNormalFloatException : public std::runtime_error {
public:
    NonNormalFloatException(double value, const std::string& msg)
        : runtime_error("Non-Normal float read: (" + std::to_string(value) + ") \"" + msg + "\"")
    {}
};
