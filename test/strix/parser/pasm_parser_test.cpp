#include "strix/parser/pasm_parser.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "strix/common/register.hpp"
#include "strix/common/type.hpp"

namespace strix {
namespace parser {

using common::Argument;
using common::Register;
using common::Type;

class MatcherPasmParser : public PasmParser {
public:
    MOCK_METHOD(void, onCommand, (std::string iCommand), (override));
    MOCK_METHOD(void, onArgument, (Argument iArgument), (override));
};

class PasmParserTest : public ::testing::Test {
protected:
    PasmParserTest() = default;
    ~PasmParserTest() override = default;

    MatcherPasmParser _parser;
};


TEST_F(PasmParserTest, shouldParseCommand_WhenNoArgument) {
    EXPECT_CALL(_parser, onCommand("end"));
    _parser.parseExpression(PasmParser::State::kStart, "end");
}

TEST_F(PasmParserTest, shouldParseArgument_WhenLong) {
    EXPECT_CALL(_parser, onArgument({711l}));
    _parser.parseExpression(PasmParser::State::kBeforeArgument, "711");
}

TEST_F(PasmParserTest, shouldParseArgument_WhenDouble) {
    EXPECT_CALL(_parser, onArgument({42.42}));
    _parser.parseExpression(PasmParser::State::kBeforeArgument, "42.42");
}

TEST_F(PasmParserTest, shouldParseArgument_WhenString) {
    EXPECT_CALL(_parser, onArgument({"This is a test string"}));
    _parser.parseExpression(PasmParser::State::kBeforeArgument, "\"This is a test string\"");
}

TEST_F(PasmParserTest, shouldParseArgument_WhenLongRegister) {
    EXPECT_CALL(_parser, onArgument({Register{Type::LONG, 12u}}));
    _parser.parseExpression(PasmParser::State::kBeforeArgument, "I12");
}

TEST_F(PasmParserTest, shouldParseArgument_WhenDoubleRegister) {
    EXPECT_CALL(_parser, onArgument({Register{Type::DOUBLE, 12u}}));
    _parser.parseExpression(PasmParser::State::kBeforeArgument, "N12");
}

TEST_F(PasmParserTest, shouldParseArgument_WhenStringRegister) {
    EXPECT_CALL(_parser, onArgument({Register{Type::STRING, 12u}}));
    _parser.parseExpression(PasmParser::State::kBeforeArgument, "S12");
}

TEST_F(PasmParserTest, shouldParseExpression_WhenOneArgument) {
    EXPECT_CALL(_parser, onCommand("print"));
    EXPECT_CALL(_parser, onArgument({42l}));
    _parser.parseExpression(PasmParser::State::kStart, "print 42");
}

TEST_F(PasmParserTest, shouldParseExpression_WhenTwoArgument) {
    EXPECT_CALL(_parser, onCommand("set"));
    EXPECT_CALL(_parser, onArgument({Register{Type::STRING, 1u}}));
    EXPECT_CALL(_parser, onArgument({"forty two"}));
    _parser.parseExpression(PasmParser::State::kStart, "set S1, \"forty two\"");
}

TEST_F(PasmParserTest, shouldParseExpression_WhenTwoArgumentWithExtraSpaces) {
    EXPECT_CALL(_parser, onCommand("set"));
    EXPECT_CALL(_parser, onArgument({Register{Type::STRING, 1u}}));
    EXPECT_CALL(_parser, onArgument({"forty two"}));
    _parser.parseExpression(PasmParser::State::kStart, "set     S1, \"forty two\"");
}

TEST_F(PasmParserTest, shouldParseExpression_WhenTwoRegisters) {
    EXPECT_CALL(_parser, onCommand("set"));
    EXPECT_CALL(_parser, onArgument({Register{Type::STRING, 2u}}));
    EXPECT_CALL(_parser, onArgument({Register{Type::STRING, 1u}}));
    _parser.parseExpression(PasmParser::State::kStart, "set S2, S1");
}



}  // namespace parser
}  // namespace strix