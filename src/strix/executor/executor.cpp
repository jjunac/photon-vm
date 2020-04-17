#include "strix/executor/executor.hpp"

#include "strix/executor/return.hpp"


namespace strix {
namespace executor {


void Executor::execute(const common::Expression& iExpr) {
    Return aReturn = _commandFactory.getCommand(iExpr.command).run(_executionContext, iExpr.arguments);
    if (aReturn.isEnd) {
        exit(aReturn.exitCode);
    }
}

void Executor::execute(const parser::StrixParser& iParser) {
    for (auto &&anExpr : iParser.getExpressions()) {
        execute(anExpr);
    }
}


} // namespace executor
} // namespace strix