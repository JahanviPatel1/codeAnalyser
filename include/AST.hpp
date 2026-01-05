#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>

// Forward declarations
class ASTVisitor;

// Base Node
class Node {
public:
    virtual ~Node() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};

// Statements
class Statement : public Node {};

class Block : public Statement {
public:
    std::vector<std::unique_ptr<Statement>> statements;
    void accept(ASTVisitor& visitor) override;
};

class IfStatement : public Statement {
public:
    std::unique_ptr<Node> condition; // Using Node for expression
    std::unique_ptr<Statement> thenBranch;
    std::unique_ptr<Statement> elseBranch; // Can be null
    void accept(ASTVisitor& visitor) override;
};

class WhileStatement : public Statement {
public:
    std::unique_ptr<Node> condition;
    std::unique_ptr<Statement> body;
    void accept(ASTVisitor& visitor) override;
};

class ReturnStatement : public Statement {
public:
    std::unique_ptr<Node> value;
    void accept(ASTVisitor& visitor) override;
};

class ExpressionStatement : public Statement {
public:
    std::unique_ptr<Node> expression;
    void accept(ASTVisitor& visitor) override;
};

class VariableDeclaration : public Statement {
public:
    std::string type;
    std::string name;
    std::unique_ptr<Node> initializer; // Can be null
    void accept(ASTVisitor& visitor) override;
};

// Expressions (Simplified for complexity analysis)
class Expression : public Node {};

class Literal : public Expression {
public:
    std::string value;
    void accept(ASTVisitor& visitor) override;
};

class BinaryExpression : public Expression {
public:
    std::unique_ptr<Node> left;
    std::string op;
    std::unique_ptr<Node> right;
    void accept(ASTVisitor& visitor) override;
};

class Identifier : public Expression {
public:
    std::string name;
    void accept(ASTVisitor& visitor) override;
};

// Root
class FunctionDeclaration : public Node {
public:
    std::string returnType;
    std::string name;
    std::unique_ptr<Block> body;
    void accept(ASTVisitor& visitor) override;
};

class Program : public Node {
public:
    std::vector<std::unique_ptr<FunctionDeclaration>> functions;
    void accept(ASTVisitor& visitor) override;
};

// Visitor Interface
class ASTVisitor {
public:
    virtual void visit(Block& node) = 0;
    virtual void visit(IfStatement& node) = 0;
    virtual void visit(WhileStatement& node) = 0;
    virtual void visit(ReturnStatement& node) = 0;
    virtual void visit(ExpressionStatement& node) = 0;
    virtual void visit(VariableDeclaration& node) = 0;
    virtual void visit(Literal& node) = 0;
    virtual void visit(BinaryExpression& node) = 0;
    virtual void visit(Identifier& node) = 0;
    virtual void visit(FunctionDeclaration& node) = 0;
    virtual void visit(Program& node) = 0;
};
