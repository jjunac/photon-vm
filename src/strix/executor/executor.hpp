#pragma once

#include <unordered_map>

#include "strix/common/expression.hpp"
#include "strix/executor/command_factory.hpp"
#include "strix/parser/parser.hpp"

namespace strix {
namespace executor {


class Executor final {
public:
    Executor() = default;
    ~Executor() = default;

    void execute(const common::Expression& iExpression);
    void execute(const parser::Parser& iParser);

private:
    CommandFactory _commandFactory;
};


} // namespace executor
} // namespace strix

