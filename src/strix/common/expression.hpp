#pragma once

#include <vector>
#include <string>

#include "strix/common/argument.hpp"

namespace strix {
namespace common {


struct Expression {
    std::string command;
    std::vector<Argument> arguments;

    Expression() = default;
};


} // namespace common
} // namespace strix

