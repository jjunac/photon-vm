#pragma once

#include <unordered_map>

#include "strix/parser/expression.hpp"
#include "strix/parser/parser.hpp"
#include "strix/executor/command_factory.hpp"

namespace strix {
namespace executor {


class Executor final {
public:
    Executor() = default;
    ~Executor() = default;

    void execute(const parser::Expression& iExpression);
    void execute(const parser::Parser& iParser);

private:
    CommandFactory _commandFactory;
};


} // namespace executor
} // namespace strix

