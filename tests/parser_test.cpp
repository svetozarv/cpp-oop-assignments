#include <gtest/gtest.h>
#include "../include/parser.hpp"
#include "../include/lexer.hpp"

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

    EXPECT_DOUBLE_EQ(root->evaluate(5.0), 15.0);
}

TEST(ParserTest, ParsesSingleVariable) {
    Lexer lexer("x");
    Parser parser(lexer.tokenize());
    std::unique_ptr<ASTNode> root = parser.buildTree();

    EXPECT_DOUBLE_EQ(root->evaluate(7.0), 7.0);
}

TEST(ParserTest, ParsesSingleConstant) {
    Lexer lexer("8");
    Parser parser(lexer.tokenize());
    std::unique_ptr<ASTNode> root = parser.buildTree();

    EXPECT_DOUBLE_EQ(root->evaluate(5.0), 8.0);
}

TEST(ParserTest, ParsesSimpleMonomial) {
    Lexer lexer("3*x");
    Parser parser(lexer.tokenize());
    std::unique_ptr<ASTNode> root = parser.buildTree();

    // 3 * 4 = 12
    EXPECT_DOUBLE_EQ(root->evaluate(4.0), 12.0);
}

TEST(ParserTest, ParsesVariableWithExponent) {
    Lexer lexer("x^3");
    Parser parser(lexer.tokenize());
    std::unique_ptr<ASTNode> root = parser.buildTree();

    // 2 ^ 3 = 8
    EXPECT_DOUBLE_EQ(root->evaluate(2.0), 8.0);
}

TEST(ParserTest, ParsesFullPolynomialExpression) {
    Lexer lexer("2*x^3 + 4*x + 5");
    Parser parser(lexer.tokenize());
    std::unique_ptr<ASTNode> root = parser.buildTree();

    // if x = 3
    // 2*(3^3) + 4*(3) + 5
    // = 2*(27) + 12 + 5
    // = 54 + 12 + 5 = 71
    EXPECT_DOUBLE_EQ(root->evaluate(3.0), 71.0);
}
