#pragma once
#include "AST.hpp"
#include <iostream>
#include <string>

class DebugPrinter : public ASTVisitor {
    int depth = 0;

    void indent() {
        for (int i = 0; i < depth; i++) std::cout << "  ";
    }

public:
    void visit(Block& node) override {
        indent(); std::cout << "Block" << std::endl;
        depth++;
        for (auto& stmt : node.statements) {
            stmt->accept(*this);
        }
        depth--;
    }

    void visit(IfStatement& node) override {
        indent(); std::cout << "If" << std::endl;
        depth++;
        indent(); std::cout << "Condition:" << std::endl;
        node.condition->accept(*this);
        indent(); std::cout << "Then:" << std::endl;
        node.thenBranch->accept(*this);
        if (node.elseBranch) {
            indent(); std::cout << "Else:" << std::endl;
            node.elseBranch->accept(*this);
        }
        depth--;
    }

    void visit(WhileStatement& node) override {
        indent(); std::cout << "While" << std::endl;
        depth++;
        node.condition->accept(*this);
        node.body->accept(*this);
        depth--;
    }

    void visit(ReturnStatement& node) override {
        indent(); std::cout << "Return" << std::endl;
        if (node.value) {
            depth++;
            node.value->accept(*this);
            depth--;
        }
    }

    void visit(ExpressionStatement& node) override {
        indent(); std::cout << "ExprStmt" << std::endl;
        depth++;
        node.expression->accept(*this);
        depth--;
    }

    void visit(VariableDeclaration& node) override {
        indent(); std::cout << "VarDecl: " << node.type << " " << node.name << std::endl;
        if (node.initializer) {
            depth++;
            node.initializer->accept(*this);
            depth--;
        }
    }

    void visit(Literal& node) override {
        indent(); std::cout << "Literal: " << node.value << std::endl;
    }

    void visit(BinaryExpression& node) override {
        indent(); std::cout << "Binary: " << node.op << std::endl;
        depth++;
        node.left->accept(*this);
        node.right->accept(*this);
        depth--;
    }

    void visit(Identifier& node) override {
        indent(); std::cout << "ID: " << node.name << std::endl;
    }

    void visit(FunctionDeclaration& node) override {
        indent(); std::cout << "Function: " << node.returnType << " " << node.name << std::endl;
        depth++;
        node.body->accept(*this);
        depth--;
    }

    void visit(Program& node) override {
        std::cout << "Program AST:" << std::endl;
        depth++;
        for (auto& func : node.functions) {
            func->accept(*this);
        }
        depth--;
    }
};
