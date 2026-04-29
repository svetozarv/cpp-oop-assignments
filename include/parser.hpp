#pragma once
#include "../include/token.hpp"
#include <vector>
#include <memory>

class ASTNode;

class Parser {
    std::vector<Token> tokens_;
    int curr_ = 0;
    Token peek() const;
    Token consume();

public:
    Parser(std::vector<Token> tokens);

    // Handles a, x
    std::unique_ptr<ASTNode> parseDigit();

    // Monomial has digits (or variables) on the left AND on the right (ex. x^3)
    // Handles x^n, x, a
    std::unique_ptr<ASTNode> parseMonomial();

    // Term has a digit (term) on the left and a monomial on the right (ex. 2*x^3)
    // Handles a*x^n, a*x, x^n, x, a
    std::unique_ptr<ASTNode> parseTerm();

    // Expression (the input) consists of sums of terms (ex. 2*x^3 + 3*x^2)
    std::unique_ptr<ASTNode> parseExpression();

    std::unique_ptr<ASTNode> buildTree();
};
