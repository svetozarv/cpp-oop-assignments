#include "polynomial_AST.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <format>

enum class TokenType {
    X,
    NUMBER,
    EXPONENTIATION,
    MULTIPLICATION,
    ADDITION,
};

struct Token {
    TokenType type;
    char value;
};



class Lexer {
    std::string expression_;
    std::vector<Token> tokens_;
    int curr_ = 0;

    void createToken(TokenType type, char val) {
        Token token;
        token.type = type;
        token.value = val;
        tokens_.push_back(token);
    }
public:
    Lexer(std::string expression) : expression_(expression) {}

    std::vector<Token> tokenize() {
        while (curr_ < expression_.length()) {
            char symbol = expression_.at(curr_++);
            if (symbol == ' ') { continue; }
            else if (symbol == 'x') { createToken(TokenType::X, 'x'); }
            else if (symbol == '*') { createToken(TokenType::MULTIPLICATION, '*'); }
            else if (symbol == '^') { createToken(TokenType::EXPONENTIATION, '^'); }
            else if (symbol == '+') { createToken(TokenType::ADDITION, '+'); }
            else if (48 <= symbol && symbol <= 57) { createToken(TokenType::NUMBER, symbol); }
            else { throw std::runtime_error(std::format("Invalid input on token {}", symbol)); }
            // else if (48 <= symbol && symbol <= 57) {
            //     int start_digit = --curr_;
            //     while (48 <= symbol && symbol <= 57) { ++curr_; }

            //     createToken(TokenType::NUMBER, '+');
            // }
        }
        return tokens_;
    };
};


// x^3 + 2*x^2 + 4*x + 3
class Parser {
    std::vector<Token> tokens_;
    int curr_ = 0;
    Token peek() const { return tokens_.at(curr_); }
    Token consume() { return tokens_.at(curr_++); }

public:
    Parser(std::vector<Token> tokens) : tokens_(tokens) {}

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
