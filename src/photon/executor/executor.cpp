#include "photon/executor/executor.hpp"

#include "photon/executor/return.hpp"


namespace photon {
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
} // namespace photon