#pragma once

#include <string>

#include <boost/variant.hpp>

#include "strix/common/register.hpp"
#include "strix/common/type.hpp"
#include "strix/exception.hpp"

namespace strix {
namespace common {

class Argument final {
public:

    template <typename T>
    Argument(T value) : _value(value) {}

    Type getType() const {
        return Type(_value.which());
    }

    template <typename T>
    const T& get() const { return boost::get<T>(_value); }

    template <typename T>
    const T& to() const;

    bool isRegister() const { return Type(_value.which()) == Type::REGISTER; }
    bool isLong() const     { return Type(_value.which()) == Type::LONG; }
    bool isDouble() const   { return Type(_value.which()) == Type::DOUBLE; }
    bool isString() const   { return Type(_value.which()) == Type::STRING; }

    bool isRegisterType(Type iType) const   { return isRegister() && boost::get<Register>(_value).getType() == iType; }
    bool isNumeric() const                  { return isLong() || isDouble(); }
    bool isNumericRegister() const          { return isRegister() && boost::get<Register>(_value).isNumericRegister(); }

    friend inline bool operator==(const Argument& lhs, const Argument& rhs) {
        return lhs._value == rhs._value;
    }
private:
    boost::variant<Register, long, double, std::string> _value;
};


} // namespace common
} // namespace strix

