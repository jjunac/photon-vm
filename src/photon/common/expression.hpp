#pragma once

#include <vector>
#include <string>

#include "photon/common/argument.hpp"

namespace photon {
namespace common {


struct Expression {
    std::string command;
    std::vector<Argument> arguments;

    Expression() = default;
};


} // namespace common
} // namespace photon

