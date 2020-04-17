#include "strix/parser/pasm_parser.hpp"

#include "strix/common/register.hpp"


namespace strix {
namespace parser {

#define UPDATE_STATE(State)         aCurrentState = State;
#define CURRENT_STATE()             aCurrentState
#define TRANSITION(Destination)     UPDATE_STATE(Destination); continue;
#define REEXECUTE()                 goto reexecute;

#define IS_DIGIT(Ch)                '0' <= (Ch) && (Ch) <= '9'

#define UNEXPECTED_TOKEN(Position, Token) \
    throw UnexpectedTokenException(Position, Token);

void PasmParser::parseExpression(PasmParser::State iStartState, const std::string& iStr) {
    using common::Type;

    State aCurrentState = iStartState;
    std::string aCurrentString;
    Type aCurrentRegisterType;

    unsigned int anStrSize = iStr.size();
    for (unsigned int i=0; i < anStrSize; ++i) {
        char c = iStr[i];

reexecute:
        switch (aCurrentState) {

        case State::kStart:
            if (c == ' ') {
                TRANSITION(State::kStart);
            }
            aCurrentString = c;
            TRANSITION(State::kCommand);

        case State::kCommand:
            if (c == ' ') {
                onCommand(std::move(aCurrentString));
                TRANSITION(State::kBeforeArgument);
            }
            aCurrentString += c;
            TRANSITION(State::kCommand);

        case State::kBeforeArgument:
            // No matter what, we'll need to start fresh
            aCurrentString.clear();
            if (c == ' ') {
                TRANSITION(State::kBeforeArgument);
            }
            if (c == '"') {
                TRANSITION(State::kString);
            }
            if (c == 'I') {
                aCurrentRegisterType = Type::LONG;
                TRANSITION(State::kRegister);
            }
            if (c == 'N') {
                aCurrentRegisterType = Type::DOUBLE;
                TRANSITION(State::kRegister);
            }
            if (c == 'S') {
                aCurrentRegisterType = Type::STRING;
                TRANSITION(State::kRegister);
            }
            if ('0' <= c && c <= '9') {
                aCurrentString = c;
                TRANSITION(State::kLong);
            }
            UNEXPECTED_TOKEN(i, c);

        case State::kString:
            if (c == '"') {
                onArgument(std::move(aCurrentString));
                TRANSITION(State::kAfterArgument);
            }
            if (c == '\\') {
                TRANSITION(State::kStringWithBackslash);
            }
            aCurrentString += c;
            TRANSITION(State::kString);

        case State::kStringWithBackslash:
            if (c == '\\') {
                aCurrentString += '\\';
                TRANSITION(State::kString);
            }
            if (c == 'n') {
                aCurrentString += '\n';
                TRANSITION(State::kString);
            }
            if (c == 't') {
                aCurrentString += '\t';
                TRANSITION(State::kString);
            }
            if (c == '"') {
                aCurrentString += '"';
                TRANSITION(State::kString);
            }
            UNEXPECTED_TOKEN(i, c);
        
        case State::kLong:
            if ('0' <= c && c <= '9') {
                aCurrentString += c;
                TRANSITION(State::kLong);
            }
            if (c == '.') {
                aCurrentString += c;
                TRANSITION(State::kDouble);
            }
            if (c == ' ' || c == ',') {
                onArgument({std::stol(aCurrentString)});
                UPDATE_STATE(State::kAfterArgument);
                REEXECUTE();
            }
            UNEXPECTED_TOKEN(i, c);
        
        case State::kDouble:
            if ('0' <= c && c <= '9') {
                aCurrentString += c;
                TRANSITION(State::kDouble);
            }
            if (c == ' ' || c == ',') {
                onArgument({std::stod(aCurrentString)});
                UPDATE_STATE(State::kAfterArgument);
                REEXECUTE();
            }
            UNEXPECTED_TOKEN(i, c);
        
        case State::kRegister:
            if ('0' <= c && c <= '9') {
                aCurrentString += c;
                TRANSITION(State::kRegister);
            }
            if (c == ' ' || c == ',') {
                #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
                    onArgument({common::Register(aCurrentRegisterType, std::stoul(aCurrentString))});
                #pragma GCC diagnostic pop
                UPDATE_STATE(State::kAfterArgument);
                REEXECUTE();
            }
            UNEXPECTED_TOKEN(i, c);

        case State::kAfterArgument:
            if (c == ' ') {
                TRANSITION(State::kAfterArgument);
            }
            if (c == ',') {
                TRANSITION(State::kBeforeArgument);
            }
            UNEXPECTED_TOKEN(i, c);

        case State::kEnd:
        default:
            UNEXPECTED_TOKEN(i, c);
        }

    }

    switch (aCurrentState) {

    case State::kCommand:
        onCommand(std::move(aCurrentString));
        break;

    case State::kLong:
        onArgument({std::stol(aCurrentString)});
        break;

    case State::kDouble:
        onArgument({std::stod(aCurrentString)});
        break;
    
    case State::kRegister:
        #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
            onArgument({common::Register(aCurrentRegisterType, std::stoul(aCurrentString))});
        #pragma GCC diagnostic pop
        break;

    case State::kBeforeArgument:
    case State::kString:
    case State::kStringWithBackslash:
        UNEXPECTED_TOKEN(anStrSize, "EOL");

    case State::kStart:
    case State::kAfterArgument:
    case State::kEnd:
        break;
    }

}

} // namespace parser
} // namespace strix
