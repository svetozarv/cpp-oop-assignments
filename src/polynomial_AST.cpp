#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/polynomial_AST.hpp"

PolynomialAST::PolynomialAST(std::string expression) {
    Lexer lexer(expression);
    Parser parser(lexer.tokenize());
    root_ = parser.buildTree();
}

ASTNode* PolynomialAST::root() {
    return root_.get();
}

double PolynomialAST::evaluate(double x) {
    return root_.get()->evaluate(x);
}
