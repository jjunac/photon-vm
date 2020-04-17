#include "strix/parser/strix_parser.hpp"


namespace strix {
namespace parser {

using common::Expression;

StrixParser::StrixParser() :
    _expressions(),
    _lineno(1) {}

const Expression& StrixParser::parseLine(const std::string& iLine) {
    try {
        _expressions.emplace_back();
        PasmParser::parseExpression(PasmParser::State::kStart, iLine);
        ++_lineno;
    } catch (PasmParserException& e) {
        _expressions.pop_back();
        throw StrixParserException(_lineno++, e);
    }
    return _expressions.back();
}


void StrixParser::onCommand(std::string iCommand) {
    _expressions.back().command = std::move(iCommand);
}

void StrixParser::onArgument(common::Argument iArgument) {
    _expressions.back().arguments.push_back(std::move(iArgument));

}

} // namespace parser
} // namespace strix
