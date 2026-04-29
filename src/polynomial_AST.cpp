#include "../include/lexer.hpp"
#include "../include/parser.hpp"
#include "../include/polynomial_AST.hpp"
#include <stdexcept>
#include <cmath>

double BinaryOPNode::evaluate(double x) const {
    double left = getLeft()->evaluate(x);
    double right = getRight()->evaluate(x);
    switch (operator_) {
        case '^': return std::pow(left, right);
        case '*': return left * right;
        case '+': return left + right;
        default: throw std::runtime_error("BinaryOpNode contains unsupported operation.");
    }
}

PolynomialAST::PolynomialAST(std::string expression) {
    Lexer lexer(expression);
    Parser parser(lexer.tokenize());
    root_ = parser.buildTree();
}

double PolynomialAST::evaluate(double x) {
    if (!root_) throw std::runtime_error("AST root is null!");
    return root_.get()->evaluate(x);
}
