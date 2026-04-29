#include <gtest/gtest.h>
#include "../include/lexer.hpp"


TEST(LexerTest, TokenizesPolynomialWithWhitespace) {
    Lexer lexer(" 3 * x ^   2 + 46 ");
    std::vector<Token> tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 8); // ASSERT stops the test immediately if it fails

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
