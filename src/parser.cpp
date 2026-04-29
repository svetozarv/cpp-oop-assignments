#include "../include/polynomial_AST.hpp"
#include "../include/token.hpp"
#include "../include/parser.hpp"
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>


Token Parser::peek() const { return tokens_.at(curr_); }
Token Parser::consume() { return tokens_.at(curr_++); }

Parser::Parser(std::vector<Token> tokens) : tokens_(tokens) {}

std::unique_ptr<ASTNode> Parser::parseDigit() {
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

std::unique_ptr<ASTNode> Parser::parseMonomial() {
    std::unique_ptr<ASTNode> left = parseDigit();
    while (peek().type == TokenType::EXPONENTIATION) {
        Token optoken = consume();
        std::unique_ptr<ASTNode> right = parseDigit();
        left = std::make_unique<BinaryOPNode>(std::move(left), optoken.value, std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> Parser::parseTerm() {
    if (peek().type == TokenType::X) { return parseMonomial(); }
    std::unique_ptr<ASTNode> left = parseDigit();
    while (peek().type == TokenType::MULTIPLICATION) {
        Token optoken = consume();
        std::unique_ptr<ASTNode> right = parseMonomial();
        left = std::make_unique<BinaryOPNode>(std::move(left), optoken.value, std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> Parser::parseExpression() {
    std::unique_ptr<ASTNode> left = parseTerm();
    while (peek().type == TokenType::ADDITION) {
        Token optoken = consume();
        std::unique_ptr<ASTNode> right = parseTerm();
        left = std::make_unique<BinaryOPNode>(std::move(left), optoken.value, std::move(right));
    }
    return left;
}

std::unique_ptr<ASTNode> Parser::buildTree() {
    return parseExpression();
}
