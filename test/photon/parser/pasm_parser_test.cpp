#include "photon/parser/pasm_parser.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "photon/common/register.hpp"
#include "photon/common/type.hpp"

namespace photon {
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

TEST_F(PasmParserTest, shouldNotParseExpression_WhenCommented) {
    _parser.parseExpression(PasmParser::State::kStart, "#set S2, S1");
}

TEST_F(PasmParserTest, shouldNotParseArgument_WhenCommented) {
    EXPECT_CALL(_parser, onCommand("add"));
    EXPECT_CALL(_parser, onArgument({Register{Type::LONG, 1u}}));
    EXPECT_CALL(_parser, onArgument({3l}));
    _parser.parseExpression(PasmParser::State::kStart, "add I1, 3 #, 5");
}

TEST_F(PasmParserTest, shouldNotThrow_WhenCommentAfterExpression) {
    EXPECT_CALL(_parser, onCommand("print"));
    EXPECT_CALL(_parser, onArgument({"test"}));
    _parser.parseExpression(PasmParser::State::kStart, "print \"test\" # This print 'test'");
}

TEST_F(PasmParserTest, shouldParseString_WhenCommentTokenPresent) {
    EXPECT_CALL(_parser, onCommand("print"));
    EXPECT_CALL(_parser, onArgument({"#Test"}));
    _parser.parseExpression(PasmParser::State::kStart, "print \"#Test\"");
}

TEST_F(PasmParserTest, shouldNotThrow_WhenBlankLine) {
    _parser.parseExpression(PasmParser::State::kStart, "");
}

TEST_F(PasmParserTest, shouldNotThrow_WhenBlankLineWithSpace) {
    _parser.parseExpression(PasmParser::State::kStart, " ");
}



}  // namespace parser
}  // namespace photon