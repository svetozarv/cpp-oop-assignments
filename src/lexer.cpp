#include <vector>
#include <iostream>
#include <memory>
#include <string>

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
            // TODO: add numbers handling
            // else if (48 <= symbol && symbol <= 57) {
            //     int start_digit = --curr_;
            //     while (48 <= symbol && symbol <= 57) { ++curr_; }

            //     createToken(TokenType::NUMBER, '+');
            // }
        }
        return tokens_;
    };
};
