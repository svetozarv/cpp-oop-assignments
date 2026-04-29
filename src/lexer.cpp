#include "../include/lexer.hpp"
#include "../include/token.hpp"
#include <vector>
#include <string>
#include <format>
#include <stdexcept>


void Lexer::createToken(TokenType type, double val) {
    Token token;
    token.type = type;
    token.value = val;
    tokens_.push_back(token);
}

Lexer::Lexer(std::string expression) : expression_(expression) {}

std::vector<Token> Lexer::tokenize() {
    while (curr_ < expression_.length()) {
        char symbol = expression_.at(curr_++);
        if (symbol == ' ') { continue; }
        else if (symbol == 'x') { createToken(TokenType::X, 'x'); }
        else if (symbol == '*') { createToken(TokenType::MULTIPLICATION, '*'); }
        else if (symbol == '^') { createToken(TokenType::EXPONENTIATION, '^'); }
        else if (symbol == '+') { createToken(TokenType::ADDITION, '+'); }
        else if (48 <= symbol && symbol <= 57) {
            createToken(TokenType::NUMBER, symbol - '0');
            while (curr_ < expression_.length()) {
                symbol = expression_.at(curr_);
                if (48 <= symbol && symbol <= 57) {
                    tokens_.back().value = tokens_.back().value * 10 + (symbol - '0');
                    ++curr_;
                } else { break; }
            }
        }
        else { throw std::runtime_error(std::format("Invalid input on token {}", symbol)); }
    }
    createToken(TokenType::END, '\0');
    return tokens_;
};
