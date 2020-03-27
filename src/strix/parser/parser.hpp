#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "strix/common/expression.hpp"

namespace strix {
namespace parser {


class ParserException : public std::exception {
public:
    ParserException(const std::string& iWhat) : _what(iWhat) {}
    const char* what() const noexcept override { return _what.data(); }
private:
    std::string _what;
};

class Parser final {
private:
    enum class State {
        kStart = 0,
        kCommand,
        kBeforeArgument,
        kString,
        kStringWithBackslash,
        kLong,
        kDouble,
        kAfterArgument,
        kEnd
    };

public:
    Parser();
    ~Parser() = default;

    const std::vector<common::Expression>& getExpressions() const { return _expressions; }

    common::Expression& parseLine(const std::string& iLine);
    State parseChar(char iCh, common::Expression& iExpr);
    void endLine(common::Expression& iExpr);

private:
    std::vector<common::Expression> _expressions;
    State _state;
    std::string _currentString;
    unsigned int _lineno;
    unsigned int _columnno;
};


} // namespace parser
} // namespace strix

