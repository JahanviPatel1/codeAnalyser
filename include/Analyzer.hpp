#pragma once
#include "AST.hpp"
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

struct Metrics {
    int cyclomaticComplexity = 1; // Base is 1
    int maxNestingDepth = 0;
    int unusedVariables = 0;
    // ...
};

class Analyzer : public ASTVisitor {
public:
    Analyzer() = default;

    Metrics getMetrics() const {
        return metrics;
    }
    
    // Visitor implementations
    
    void visit(Block& node) override {
        currentDepth++;
        if (currentDepth > metrics.maxNestingDepth) {
            metrics.maxNestingDepth = currentDepth;
        }
        
        for (auto& stmt : node.statements) {
            stmt->accept(*this);
        }
        currentDepth--;
    }

    void visit(IfStatement& node) override {
        metrics.cyclomaticComplexity++;
        node.condition->accept(*this);
        node.thenBranch->accept(*this);
        if (node.elseBranch) node.elseBranch->accept(*this);
    }

    void visit(WhileStatement& node) override {
        metrics.cyclomaticComplexity++;
        node.condition->accept(*this);
        node.body->accept(*this);
    }
    
    void visit(ExpressionStatement& node) override {
        node.expression->accept(*this);
    }

    void visit(VariableDeclaration& node) override {
        // Track variable declaration
        declaredVariables[node.name] = false; // false = unused
        if (node.initializer) {
            node.initializer->accept(*this);
        }
    }
    
    void visit(Identifier& node) override {
        // Track variable usage
        if (declaredVariables.find(node.name) != declaredVariables.end()) {
            declaredVariables[node.name] = true; // Mark as used
        }
    }
    
    // Passthroughs
    void visit(ReturnStatement& node) override { if(node.value) node.value->accept(*this); }
    void visit(Literal& node) override {}
    void visit(BinaryExpression& node) override { 
        node.left->accept(*this); 
        node.right->accept(*this); 
        if (node.op == "&&" || node.op == "||") {
            metrics.cyclomaticComplexity++; // Boolean operators increase complexity
        }
    }
    void visit(FunctionDeclaration& node) override {
        // Reset metrics for each function? Or aggregate? 
        // For now, let's aggregate for the whole file
        node.body->accept(*this);
    }
    
    void visit(Program& node) override {
        for (auto& func : node.functions) {
            func->accept(*this);
        }
        calculateUnused();
    }
    
private:
    Metrics metrics;
    int currentDepth = 0;
    std::map<std::string, bool> declaredVariables;

    void calculateUnused() {
        int count = 0;
        for (auto const& [name, used] : declaredVariables) {
            if (!used) count++;
        }
        metrics.unusedVariables = count;
    }
};
