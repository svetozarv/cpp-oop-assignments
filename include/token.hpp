#pragma once
// #include <iostream>

enum class TokenType {
    X,
    NUMBER,
    EXPONENTIATION,
    MULTIPLICATION,
    ADDITION,
    END,
};

struct Token {
    TokenType type;
    double value;
};

// std::ostream& operator<<(std::ostream& os, const Token& token) {
//     switch (token.type) {
//         case TokenType::X: os << "X"; break;
//         case TokenType::NUMBER: os << "NUMBER(" << token.value << ")"; break;
//         case TokenType::EXPONENTIATION: os << "EXPONENTIATION(^)"; break;
//         case TokenType::MULTIPLICATION: os << "MULTIPLICATION(*)"; break;
//         case TokenType::ADDITION: os << "ADDITION(+)"; break;
//         case TokenType::END: os << "END"; break;
//     }
//     return os;
// }