#pragma once
#include "../include/token.hpp"
#include <vector>
#include <string>

class Lexer {
    std::string expression_;
    std::vector<Token> tokens_;
    int curr_ = 0;
    void createToken(TokenType type, double val);
public:
    Lexer(std::string expression);
    std::vector<Token> tokenize();
};
