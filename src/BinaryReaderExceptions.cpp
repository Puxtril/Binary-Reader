#include "BinaryReaderExceptions.h"

LimitException::LimitException(uint64_t value, uint64_t limit, const std::string& msg)
    : runtime_error("Limit (" + std::to_string(limit) + ") hit: " + std::to_string(value) + " \"" + msg + "\"")
{}

LimitException::LimitException(int64_t value, int64_t limit, const std::string& msg)
    : runtime_error("Limit (" + std::to_string(limit) + ") hit: " + std::to_string(value) + " \"" + msg + "\"")
{}

LimitException::LimitException(double value, double limit, const std::string& msg)
    : runtime_error("Limit (" + std::to_string(limit) + ") hit: " + std::to_string(value) + " \"" + msg + "\"")
{}

NonNormalFloatException::NonNormalFloatException(double value, const std::string& msg)
    : runtime_error("Non-Normal float read: (" + std::to_string(value) + ") \"" + msg + "\"")
{}
