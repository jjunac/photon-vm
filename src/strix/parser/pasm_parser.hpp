#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "strix/common/register.hpp"
#include "strix/common/argument.hpp"

namespace strix {
namespace parser {


class PasmParserException : public std::exception {
public:
    PasmParserException(unsigned int iPosition, const std::string& iWhat) : _position(iPosition), _what(iWhat) {}
    const char* what() const noexcept override { return _what.data(); }
    unsigned int virtual position() const noexcept { return _position; }
private:
    unsigned int _position;
    std::string _what;
};

class UnexpectedTokenException : public PasmParserException {
public:
    UnexpectedTokenException(unsigned int iPosition, const std::string& iToken) 
        : PasmParserException(iPosition, std::string("Unexpected '") + iToken + "'") {}
    UnexpectedTokenException(unsigned int iPosition, char iToken) 
        : PasmParserException(iPosition, std::string("Unexpected '") + iToken + "'") {}
};

class PasmParser {
public:
    enum class State {
        kStart = 0,
        kCommand,
        kBeforeArgument,
        kString,
        kStringWithBackslash,
        kLong,
        kDouble,
        kRegister,
        kAfterArgument,
        kEnd
    };

    PasmParser() = default;
    virtual ~PasmParser() = default;

    void parseExpression(PasmParser::State iStartState, const std::string& iStr);

    //Callbacks
    virtual void onCommand(std::string iCommand) = 0;
    virtual void onArgument(common::Argument iArgument) = 0;
};


} // namespace parser
} // namespace strix

