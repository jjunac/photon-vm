#pragma once

#include <string>

#include <boost/variant.hpp>

#include "strix/common/registry.hpp"

namespace strix {
namespace common {

class Argument final {
public:
    enum Type : int {
        LONG = 0,
        DOUBLE = 1,
        STRING = 2,
        REGISTRY = 3
    };

    template <typename T>
    Argument(T value) : _value(value) {}

    int getType() const {
        return _value.which();
    }

    bool isLong() const { return _value.which() == Type::LONG; }
    long getLong() const { return boost::get<long>(_value); }

    bool isDouble() const { return _value.which() == Type::DOUBLE; }
    double getDouble() const { return boost::get<double>(_value); }

    bool isString() const { return _value.which() == Type::STRING; }
    std::string getString() const { return boost::get<std::string>(_value); }

    bool isRegistry() const { return _value.which() == Type::REGISTRY; }
    Registry getRegistry() const { return boost::get<Registry>(_value); }

private:
    boost::variant<long, double, std::string, Registry> _value;
};

} // namespace common
} // namespace strix

