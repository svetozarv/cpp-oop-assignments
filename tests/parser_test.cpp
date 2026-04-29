#include <gtest/gtest.h>
#include "../src/parser.cpp"
#include <iostream>

TEST(ParserTest, ParsesSimpleExpression) {
    Lexer lexer("2*x^3 + 3*x^2 + 4*x + 5");
    Parser parser(lexer.tokenize());
    std::unique_ptr<ASTNode> root = parser.parseExpression();

    // Evaluate at x = 1. Expected: 2 + 3 + 4 + 5 = 14
    EXPECT_DOUBLE_EQ(root->evaluate(1.0), 14.0);
}

TEST(ParserTest, EnforcesOperatorPrecedence) {
    // If precedence is wrong, 2*x^2 might become (2*x)^2
    Lexer lexer("x^3 + 2*x^2 + 4*x + 3");
    Parser parser(lexer.tokenize());
    std::unique_ptr<ASTNode> root = parser.parseExpression();

    // Evaluate at x = 2
    // Expected: (2^3) + 2*(2^2) + 4*(2) + 3 = 8 + 8 + 8 + 3 = 27
    EXPECT_DOUBLE_EQ(root->evaluate(2.0), 27.0);
}

TEST(ParserTest, HandlesLeftAssociativity) {
    Lexer lexer("x + x + x");
    std::vector<Token> tokens = lexer.tokenize();
    Parser parser(tokens);
    std::unique_ptr<ASTNode> root = parser.parseExpression();

    // Evaluate at x = 5. Expected: 15
    EXPECT_DOUBLE_EQ(root->evaluate(5.0), 15.0);
}
