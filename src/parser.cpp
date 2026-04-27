#include "polynomial_AST.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <format>


class Parser {
    std::vector<Token> tokens_;
    int curr_ = 0;
    Token peek() const { return tokens_.at(curr_); }
    Token consume() { return tokens_.at(curr_++); }

public:
    Parser(std::vector<Token> tokens) : tokens_(tokens) {}

    // Handles a, x
    std::unique_ptr<ASTNode> parseDigit() {
        Token token = peek();
        switch (token.type) {
            case TokenType::NUMBER:
                consume();
                return std::make_unique<LiteralNode>(token.value);
            case TokenType::X:
                consume();
                return std::make_unique<VariableNode>();
            default:
                throw std::runtime_error("Expected X or NUMBER.");
        }
    }

    // Monomial has digits (or variables) on the left AND on the right (ex. x^3)
    // Handles x^n, x, a
    std::unique_ptr<ASTNode> parseMonomial() {
        std::unique_ptr<ASTNode> left = parseDigit();
        while (peek().type == TokenType::EXPONENTIATION) {
            Token optoken = consume();
            std::unique_ptr<ASTNode> right = parseDigit();
            left = std::make_unique<BinaryOPNode>(std::move(left), optoken.value, std::move(right));
        }
        return left;
    }

    // Term has a digit (term) on the left and a monomial on the right (ex. 2*x^3)
    // Handles a*x^n, a*x, x^n, x, a
    std::unique_ptr<ASTNode> parseTerm() {
        if (peek().type == TokenType::X) { return parseMonomial(); }

        std::unique_ptr<ASTNode> left = parseDigit();
        while (peek().type == TokenType::MULTIPLICATION) {
            Token optoken = consume();
            std::unique_ptr<ASTNode> right = parseMonomial();
            left = std::make_unique<BinaryOPNode>(std::move(left), optoken.value, std::move(right));
        }
        return left;
    }

    // Expression (the input) consists of sums of terms (ex. 2*x^3 + 3*x^2)
    std::unique_ptr<ASTNode> parseExpression() {
        std::unique_ptr<ASTNode> left = parseTerm();
        while (peek().type == TokenType::ADDITION) {
            Token optoken = consume();
            std::unique_ptr<ASTNode> right = parseTerm();
            left = std::make_unique<BinaryOPNode>(std::move(left), optoken.value, std::move(right));
        }
        return left;
    }
};
