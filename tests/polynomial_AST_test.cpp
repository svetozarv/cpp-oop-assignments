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

