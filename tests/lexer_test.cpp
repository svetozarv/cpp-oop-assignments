#include <gtest/gtest.h>
#include "../include/lexer.hpp"


TEST(LexerTest, TokenizesPolynomialWithWhitespace) {
    Lexer lexer(" 3 * x ^   2 + 46 ");
    std::vector<Token> tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 8);

    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(tokens[0].value, 3.0);

    EXPECT_EQ(tokens[1].type, TokenType::MULTIPLICATION);
    EXPECT_EQ(tokens[2].type, TokenType::X);
    EXPECT_EQ(tokens[3].type, TokenType::EXPONENTIATION);

    EXPECT_EQ(tokens[4].type, TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(tokens[4].value, 2.0);

    EXPECT_EQ(tokens[5].type, TokenType::ADDITION);

    EXPECT_EQ(tokens[6].type, TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(tokens[6].value, 46.0);
}

TEST(LexerTest, HandlesEdgeCases) {
    Lexer lexer("x + 5");
    std::vector<Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens[0].type, TokenType::X);
    EXPECT_EQ(tokens[1].type, TokenType::ADDITION);
    EXPECT_EQ(tokens[2].type, TokenType::NUMBER);
    EXPECT_DOUBLE_EQ(tokens[2].value, 5.0);
}

TEST(LexerTest, HandlesTightlyPackedExpressions) {
    Lexer lexer("2*x^3+5");
    std::vector<Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 8); // 7 symbols + 1 EOF
    EXPECT_EQ(tokens[0].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[1].type, TokenType::MULTIPLICATION);
    EXPECT_EQ(tokens[2].type, TokenType::X);
    EXPECT_EQ(tokens[3].type, TokenType::EXPONENTIATION);
    EXPECT_EQ(tokens[4].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[5].type, TokenType::ADDITION);
    EXPECT_EQ(tokens[6].type, TokenType::NUMBER);
    EXPECT_EQ(tokens[7].type, TokenType::END);
}

TEST(LexerTest, GuaranteesEOFTokenAtEnd) {
    Lexer lexer("x");
    std::vector<Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens.back().type, TokenType::END);
}

TEST(LexerTest, HandlesEmptyString) {
    Lexer lexer("");
    std::vector<Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::END);
}

TEST(LexerTest, ThrowsExceptionOnInvalidCharacter) {
    Lexer lexer("3 * x ^ 2 + $");
    EXPECT_THROW({ lexer.tokenize(); }, std::runtime_error);
}

TEST(LexerTest, IgnoresConsecutiveWhitespace) {
    Lexer lexer("x      +      2");
    std::vector<Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens[0].type, TokenType::X);
    EXPECT_EQ(tokens[1].type, TokenType::ADDITION);
    EXPECT_EQ(tokens[2].type, TokenType::NUMBER);
}
