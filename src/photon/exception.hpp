#pragma once

#include <string>
#include <stdexcept>

namespace photon {
namespace exception {


class StrixException : public std::exception {
public:
    StrixException(const std::string& iWhat) : _what(iWhat) {}
    const char* what() const noexcept override { return _what.data(); }
private:
    std::string _what;
};

class BadConversion : public StrixException {
public:
    BadConversion() : StrixException("bad conversion") {}
};

} // namespace exception
} // namespace photon

