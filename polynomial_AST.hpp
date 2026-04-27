#include <vector>
#include <iostream>
#include <memory>
#include <string>

// składają się wyłącznie z sumy jednomianów, np.: x^3 + 2*x^2 + 4*x + 3
// * każdy jednomian ma jedną z postaci: a*x^n, a*x, x^n, x, a (stała)

enum class NodeType {
    BINARY_OP_NODE, // either *, ^, or +
    LITERAL_NODE,   // node with a constant
    VARIABLE_NODE,  // x
};


class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual NodeType getKind() const = 0;
    virtual double evaluate(double x) const = 0;
    virtual std::vector<ASTNode*> getChildren() const { return {}; }
};


class LiteralNode : public ASTNode {
    double val_;
public:
    LiteralNode(double value) : val_(value) {}
    double evaluate(double x) const { return val_; }
    NodeType getKind() const override { return NodeType::LITERAL_NODE; }
};


class VariableNode : public ASTNode {
public:
    VariableNode() {}
    NodeType getKind() const override { return NodeType::VARIABLE_NODE; }
    double evaluate(double x) const { return x; }
};


class BinaryOPNode : public ASTNode {
    char operator_;
    std::unique_ptr<ASTNode> left_;
    std::unique_ptr<ASTNode> right_;
public:
    BinaryOPNode(std::unique_ptr<ASTNode> arg1, char op, std::unique_ptr<ASTNode> arg2) : operator_(op), left_(std::move(arg1)), right_(std::move(arg2)) {}
    NodeType getKind() const override { return NodeType::BINARY_OP_NODE; }
    std::vector<ASTNode*> getChildren() const { return {left_.get(), right_.get()}; }

    // --- BinaryNode specific methods ---
    char getOperator() const { return operator_; }
    ASTNode* getLeft() const { return left_.get(); }
    ASTNode* getRight() const { return right_.get(); }
};

