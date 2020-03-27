#pragma once

#include <string>

#include <boost/variant.hpp>

namespace strix {
namespace common {

class Registry {
public:
    enum Type : uint32_t {
        LONG = 0,
        DOUBLE = 1,
        STRING = 2,
        PMC = 3
    };

    Registry(Type iType, uint32_t iNumber)
            : _value(iNumber) {
        _value &= ~(0b11 << 30);
        _value |= ~(iType << 30);
    }
    ~Registry() = default;

    bool isLongRegister() const { return !(_value ^ (Type::LONG << 30)); }
    bool isDoubleRegister() const { return !(_value ^ (Type::DOUBLE << 30)); }
    bool isStringRegister() const { return !(_value ^ (Type::STRING << 30)); }
    bool isPmcRegister() const { return !(_value ^ (Type::PMC << 30)); }

    uint32_t getRegistryNumber() const { return _value & ~(0b11 << 30); }

private:
    uint32_t _value;
};

} // namespace common
} // namespace strix

