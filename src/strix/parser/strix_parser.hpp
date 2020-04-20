#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "strix/common/expression.hpp"
#include "strix/common/register.hpp"
#include "strix/parser/pasm_parser.hpp"

namespace strix {
namespace parser {

class StrixParserException : public std::exception {
public:
    StrixParserException(unsigned int iLine, unsigned int iPosition, const std::string& iWhat) 
        : _line(iLine), _position(iPosition), _what(iWhat) {}
    StrixParserException(unsigned int iLine, const PasmParserException& iPasmParserException) 
        : _line(iLine), _position(iPasmParserException.position()), _what(iPasmParserException.what()) {}
    const char* what() const noexcept override { return _what.data(); }
    unsigned int virtual line() const noexcept { return _line; }
    unsigned int virtual position() const noexcept { return _position; }
private:
    unsigned int _line;
    unsigned int _position;
    std::string _what;
};

class StrixParser : public PasmParser {
public:

    StrixParser();
    ~StrixParser() = default;

    const std::vector<common::Expression>& getExpressions() const { return _expressions; }

    void parseLine(const std::string& iLine);

    //Callbacks
    void onCommand(std::string iCommand) override;
    void onArgument(common::Argument iArgument) override;

private:
    std::vector<common::Expression> _expressions;
    unsigned int _lineno;
};


} // namespace parser
} // namespace strix

