#pragma once

#include <unordered_map>

#include "photon/common/expression.hpp"
#include "photon/executor/command_factory.hpp"
#include "photon/executor/execution_context.hpp"
#include "photon/parser/photon_parser.hpp"


namespace photon {
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
} // namespace photon

