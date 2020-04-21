#pragma once

#include <string>
#include <iostream>

#include <boost/variant.hpp>

#include "photon/common/type.hpp"

namespace photon {
namespace common {

class Register {
public:

    Register(Type iType, uint32_t iNumber) :
        _type(iType),
        _number(iNumber) {}
    ~Register() = default;

    uint32_t getRegisterNumber() const  { return _number; }
    Type getType() const                { return _type; }

    bool isLongRegister() const         { return _type == Type::LONG; }
    bool isDoubleRegister() const       { return _type == Type::DOUBLE; }
    bool isStringRegister() const       { return _type == Type::STRING; }

    bool isNumericRegister() const      { return isLongRegister() || isDoubleRegister(); }

    friend inline bool operator==(const Register& lhs, const Register& rhs) {
        return (lhs._type == rhs._type) && (lhs._number == rhs._number);
    }
private:
    Type _type;
    uint32_t _number;
};

} // namespace common
} // namespace photon

