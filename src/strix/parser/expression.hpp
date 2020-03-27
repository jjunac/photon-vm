#pragma once

#include <vector>
#include <string>

namespace strix {
namespace parser {


struct Expression {
    std::string command;
    std::vector<std::string> arguments;

    Expression() = default;
};

} // namespace parser
} // namespace strix

