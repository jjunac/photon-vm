#pragma once

#include <unordered_map>

#include "strix/common/expression.hpp"
#include "strix/executor/command_factory.hpp"
#include "strix/executor/execution_context.hpp"
#include "strix/parser/strix_parser.hpp"


namespace strix {
namespace executor {


class Executor final {
public:
    Executor() = default;
    ~Executor() = default;

    void execute(const common::Expression& iExpression);
    void execute(const parser::StrixParser& iParser);

private:
    CommandFactory _commandFactory;
    ExecutionContext _executionContext;
};


} // namespace executor
} // namespace strix

