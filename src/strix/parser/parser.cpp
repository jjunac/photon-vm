#include "strix/parser/parser.hpp"


namespace strix {
namespace parser {


Expression& Parser::parseLine(const std::string& iLine) {
    Expression anExpr;

    _state = State::kStart;
    for (char c : iLine) {
        if ((_state = parseChar(c, anExpr)) == State::kEnd) {
            break;
        }
    }
    endLine(anExpr);
    // TODO: check if state != end ?

    _expressions.push_back(anExpr);
    return _expressions.back();
}

Parser::State Parser::parseChar(char iCh, Expression& iExpr) {
    switch (_state) {

    case State::kStart:
        if (iCh == ' ') {
            return State::kStart;
        }
        _currentToken = iCh;
        return State::kCommand;

    case State::kCommand:
        if (iCh == ' ') {
            iExpr.command = std::move(_currentToken);
            return State::kBeforeArgument;
        }
        _currentToken += iCh;
        return State::kCommand;

    case State::kBeforeArgument:
        if (iCh == ' ') {
            return State::kBeforeArgument;
        }
        if (iCh == '"') {
            _currentToken.clear();
            return State::kString;
        }
        // TODO: not taken into account
        return State::kEnd;

    case State::kString:
        if (iCh == '"') {
            iExpr.arguments.push_back(std::move(_currentToken));
            return State::kAfterArgument;
        }
        if (iCh == '\\') {
            return State::kStringWithBackslash;
        }
        _currentToken += iCh;
        return State::kString;

    case State::kStringWithBackslash:
        if (iCh == '\\') {
            _currentToken += '\\';
            return State::kString;
        }
        if (iCh == 'n') {
            _currentToken += '\n';
            return State::kString;
        }
        if (iCh == 't') {
            _currentToken += '\t';
            return State::kString;
        }
        if (iCh == '"') {
            _currentToken += '"';
            return State::kString;
        }
        // TODO: not taken into account
        return State::kEnd;

    case State::kAfterArgument:
        if (iCh == ' ') {
            return State::kAfterArgument;
        }
        if (iCh == ',') {
            return State::kBeforeArgument;
        }
        // TODO: not taken into account
        return State::kEnd;

    case State::kEnd:
    default:
        return State::kEnd;
    }
}

void Parser::endLine(Expression& iExpr) {
    switch (_state) {

    case State::kCommand:
        iExpr.command = std::move(_currentToken);
        return;

    case State::kStart:
    case State::kBeforeArgument:
    case State::kString:
    case State::kStringWithBackslash:
    case State::kAfterArgument:
    case State::kEnd:
        // TODO: throw something
        return;
    }
}


} // namespace parser
} // namespace strix
