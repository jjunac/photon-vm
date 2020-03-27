#include "strix/parser/parser.hpp"


namespace strix {
namespace parser {

using common::Expression;

Parser::Parser() :
        _expressions(),
        _state(),
        _currentString(),
        _lineno(1),
        _columnno()
{}

Expression& Parser::parseLine(const std::string& iLine) {
    Expression anExpr;

    _state = State::kStart;
    _columnno = 1;
    for (char c : iLine) {
        if ((_state = parseChar(c, anExpr)) == State::kEnd) {
            break;
        }
        ++_columnno;
    }
    endLine(anExpr);
    _expressions.push_back(anExpr);
    // TODO: check if state != end ?
    ++_lineno;
    return _expressions.back();
}

#define UNEXPECTED_TOKEN(Token) \
    throw ParserException(std::string("Unexpected '") + Token + "' at line " + std::to_string(_lineno)+ " column " + std::to_string(_columnno))

Parser::State Parser::parseChar(char iCh, Expression& iExpr) {
    switch (_state) {

    case State::kStart:
        if (iCh == ' ') {
            return State::kStart;
        }
        _currentString = iCh;
        return State::kCommand;

    case State::kCommand:
        if (iCh == ' ') {
            iExpr.command = std::move(_currentString);
            return State::kBeforeArgument;
        }
        _currentString += iCh;
        return State::kCommand;

    case State::kBeforeArgument:
        if (iCh == ' ') {
            return State::kBeforeArgument;
        }
        if (iCh == '"') {
            _currentString.clear();
            return State::kString;
        }
        if ('0' <= iCh && iCh <= '9') {
            _currentString.clear();
            _currentString = iCh;
            return State::kLong;
        }
        UNEXPECTED_TOKEN(iCh);

    case State::kString:
        if (iCh == '"') {
            iExpr.arguments.emplace_back(std::move(_currentString));
            return State::kAfterArgument;
        }
        if (iCh == '\\') {
            return State::kStringWithBackslash;
        }
        _currentString += iCh;
        return State::kString;
    
    case State::kLong:
        if ('0' <= iCh && iCh <= '9') {
            _currentString += iCh;
            return State::kLong;
        }
        if (iCh == '.') {
            _currentString += iCh;
            return State::kDouble;
        }
        if (iCh == ' ') {
            iExpr.arguments.emplace_back(std::stol(_currentString));
            return State::kAfterArgument;
        }
        UNEXPECTED_TOKEN(iCh);
    
    case State::kDouble:
        if ('0' <= iCh && iCh <= '9') {
            _currentString += iCh;
            return State::kDouble;
        }
        if (iCh == ' ') {
            iExpr.arguments.emplace_back(std::stod(_currentString));
            return State::kAfterArgument;
        }
        UNEXPECTED_TOKEN(iCh);

    case State::kStringWithBackslash:
        if (iCh == '\\') {
            _currentString += '\\';
            return State::kString;
        }
        if (iCh == 'n') {
            _currentString += '\n';
            return State::kString;
        }
        if (iCh == 't') {
            _currentString += '\t';
            return State::kString;
        }
        if (iCh == '"') {
            _currentString += '"';
            return State::kString;
        }
        UNEXPECTED_TOKEN(iCh);

    case State::kAfterArgument:
        if (iCh == ' ') {
            return State::kAfterArgument;
        }
        if (iCh == ',') {
            return State::kBeforeArgument;
        }
        UNEXPECTED_TOKEN(iCh);

    case State::kEnd:
    default:
        UNEXPECTED_TOKEN(iCh);
    }
}

void Parser::endLine(Expression& iExpr) {
    switch (_state) {

    case State::kCommand:
        iExpr.command = std::move(_currentString);
        return;

    case State::kLong:
        iExpr.arguments.emplace_back(std::stol(_currentString));
        return;

    case State::kDouble:
        iExpr.arguments.emplace_back(std::stod(_currentString));
        return;

    case State::kBeforeArgument:
    case State::kString:
    case State::kStringWithBackslash:
        UNEXPECTED_TOKEN("EOF");

    case State::kStart:
    case State::kAfterArgument:
    case State::kEnd:
        return;
    }
}


} // namespace parser
} // namespace strix
