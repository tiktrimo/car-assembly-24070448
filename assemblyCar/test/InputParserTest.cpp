#include "gtest/gtest.h"
#include "../InputParser.h"

// Phase 3: char buf[] / strtok_s / strtol 대신 std::string 기반 입력 파싱

class InputParserTest : public ::testing::Test {
protected:
    InputParser parser;
};

TEST_F(InputParserTest, ParseNumber_ValidInt_ReturnsValue) {
    auto result = parser.parseNumber("1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 1);
}

TEST_F(InputParserTest, ParseNumber_ThreeReturnsThree) {
    auto result = parser.parseNumber("3");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 3);
}

TEST_F(InputParserTest, ParseNumber_ZeroReturnsZero) {
    auto result = parser.parseNumber("0");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), 0);
}

TEST_F(InputParserTest, ParseNumber_NonNumericString_ReturnsNullopt) {
    auto result = parser.parseNumber("abc");
    EXPECT_FALSE(result.has_value());
}

TEST_F(InputParserTest, ParseNumber_EmptyString_ReturnsNullopt) {
    auto result = parser.parseNumber("");
    EXPECT_FALSE(result.has_value());
}

TEST_F(InputParserTest, ParseNumber_MixedString_ReturnsNullopt) {
    auto result = parser.parseNumber("1a");
    EXPECT_FALSE(result.has_value());
}

TEST_F(InputParserTest, IsExitCommand_Exit_ReturnsTrue) {
    EXPECT_TRUE(parser.isExitCommand("exit"));
}

TEST_F(InputParserTest, IsExitCommand_Number_ReturnsFalse) {
    EXPECT_FALSE(parser.isExitCommand("1"));
}

TEST_F(InputParserTest, IsExitCommand_Empty_ReturnsFalse) {
    EXPECT_FALSE(parser.isExitCommand(""));
}
