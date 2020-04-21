#include "photon/parser/photon_parser.hpp"


namespace photon {
namespace parser {

using common::Expression;

StrixParser::StrixParser() :
    _expressions(),
    _lineno(1) {}

void StrixParser::parseLine(const std::string& iLine) {
    try {
        _expressions.emplace_back();
        PasmParser::parseExpression(PasmParser::State::kStart, iLine);
        // TODO: this is ugly
        if (_expressions.back().command.empty()) {
            // Was a blank line
            _expressions.pop_back();
        }
        ++_lineno;
    } catch (PasmParserException& e) {
        _expressions.pop_back();
        throw StrixParserException(_lineno++, e);
    }
}


void StrixParser::onCommand(std::string iCommand) {
    _expressions.back().command = std::move(iCommand);
}

void StrixParser::onArgument(common::Argument iArgument) {
    _expressions.back().arguments.push_back(std::move(iArgument));

}

} // namespace parser
} // namespace photon
