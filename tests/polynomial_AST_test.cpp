#include <gtest/gtest.h>
#include "../include/polynomial_AST.hpp"
#include <vector>
#include <memory>


TEST(PolynomialAST, EvaluatesSingleTerm) {
    // Construct tree for: 3 * x^2
    auto xNode = std::make_unique<VariableNode>();
    auto expNum = std::make_unique<LiteralNode>(2);
    auto powerNode = std::make_unique<BinaryOPNode>(std::move(xNode), '^', std::move(expNum));

    auto coeffNum = std::make_unique<LiteralNode>(3);
    auto multNode = std::make_unique<BinaryOPNode>(std::move(coeffNum), '*', std::move(powerNode));

    // Evaluate at x = 4. Expected: 3 * (4^2) = 48
    EXPECT_DOUBLE_EQ(multNode->evaluate(4.0), 48.0);
}

TEST(PolynomialAST, EvaluatesConstant) {
    auto constNode = std::make_unique<LiteralNode>(7);

    // Evaluate at x = 99. Expected: 7 (x should not matter)
    EXPECT_DOUBLE_EQ(constNode->evaluate(99.0), 7.0);
}

TEST(PolynomialAST, EvaluatesAdditionIndependently) {
    auto left = std::make_unique<LiteralNode>(5.0);
    auto right = std::make_unique<LiteralNode>(10.0);
    auto addNode = std::make_unique<BinaryOPNode>(std::move(left), '+', std::move(right));

    EXPECT_DOUBLE_EQ(addNode->evaluate(0.0), 15.0);
}

TEST(PolynomialAST, EvaluatesMultiplicationIndependently) {
    auto left = std::make_unique<LiteralNode>(4.0);
    auto right = std::make_unique<VariableNode>();
    auto multNode = std::make_unique<BinaryOPNode>(std::move(left), '*', std::move(right));

    EXPECT_DOUBLE_EQ(multNode->evaluate(3.5), 14.0);
}

TEST(PolynomialAST, EvaluatesExponentiationIndependently) {
    auto base = std::make_unique<VariableNode>();
    auto exponent = std::make_unique<LiteralNode>(3.0);
    auto powerNode = std::make_unique<BinaryOPNode>(std::move(base), '^', std::move(exponent));

    EXPECT_DOUBLE_EQ(powerNode->evaluate(4.0), 64.0);
}

TEST(PolynomialAST, ThrowsExceptionOnInvalidOperator) {
    auto left = std::make_unique<LiteralNode>(1.0);
    auto right = std::make_unique<LiteralNode>(2.0);

    auto invalidNode = std::make_unique<BinaryOPNode>(std::move(left), '/', std::move(right));

    EXPECT_THROW({ invalidNode->evaluate(5.0); }, std::runtime_error);
}

TEST(PolynomialAST, EvaluatesZeroCoefficient) {
    auto xNode = std::make_unique<VariableNode>();
    auto expNum = std::make_unique<LiteralNode>(2.0);
    auto powerNode = std::make_unique<BinaryOPNode>(std::move(xNode), '^', std::move(expNum));

    auto zeroCoeff = std::make_unique<LiteralNode>(0.0);
    auto multNode = std::make_unique<BinaryOPNode>(std::move(zeroCoeff), '*', std::move(powerNode));

    EXPECT_DOUBLE_EQ(multNode->evaluate(99.9), 0.0);
}