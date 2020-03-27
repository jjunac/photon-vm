#pragma once

#include <vector>
#include <string>

#include "strix/parser/expression.hpp"

namespace strix {
namespace parser {


class Parser final {
private:
    enum class State {
        kStart = 0,
        kCommand,
        kBeforeArgument,
        kString,
        kStringWithBackslash,
        kAfterArgument,
        kEnd
    };

public:
    Parser() = default;
    ~Parser() = default;

    const std::vector<Expression>& getExpressions() const { return _expressions; }

    Expression& parseLine(const std::string& iLine);
    State parseChar(char iCh, Expression& iExpr);
    void endLine(Expression& iExpr);

private:
    std::vector<Expression> _expressions;
    State _state;
    std::string _currentToken;
};


} // namespace parser
} // namespace strix

