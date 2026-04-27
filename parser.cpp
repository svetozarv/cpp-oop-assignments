#include "polynomial_AST.hpp"
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

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


// x^3 + 2*x^2 + 4*x + 3
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
            else { throw std::runtime_error("Invalid input on token " + symbol); }
            // else if (48 <= symbol && symbol <= 57) {
            //     int start_digit = --curr_;
            //     while (48 <= symbol && symbol <= 57) { ++curr_; }

            //     createToken(TokenType::NUMBER, '+');
            // }
        }
        return tokens_;
    };
};



class Parser {
    std::vector<Token> tokens_;
    int curr_ = 0;
    Token peek() {
        while (tokens_.at(curr_) == ' ') { ++curr_; }
        return tokens_.at(curr_);
    }
    Token consume() {
        while (tokens_.at(curr_) == ' ') { ++curr_; }
        return tokens_[curr_++];
    }

public:
    Parser(std::vector<Token> tokens) : tokens_(tokens) {}

    std::unique_ptr<ASTNode> parseExpression() {

    }

    std::unique_ptr<ASTNode> parseDigit() {

    }
};
