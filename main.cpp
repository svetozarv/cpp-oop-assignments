#include <iostream>
#include "include/polynomial_AST.hpp"

int main() {
    // Constructing the expression: (x + 5) * 2
    auto x = std::make_unique<VariableNode>();
    auto five = std::make_unique<LiteralNode>(5.0);

    // std::move is required to transfer ownership of the unique_ptrs
    auto addition = std::make_unique<BinaryOPNode>(std::move(x), '+', std::move(five));

    auto two = std::make_unique<LiteralNode>(2.0);
    auto multiplication = std::make_unique<BinaryOPNode>(std::move(addition), '*', std::move(two));


    // Polymorphic evaluation
    std::cout << "Expression: " << "(x + 5) * 2" << '\n';
    std::cout << "Result: " << multiplication->evaluate(10.0) << '\n';
    // Expected Output: Result: 30

    return 0;
}
