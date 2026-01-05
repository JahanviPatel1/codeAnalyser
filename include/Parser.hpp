#pragma once
#include <vector>
#include <memory>
#include "Token.hpp"
#include "AST.hpp"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);
    std::unique_ptr<Program> parse();

private:
    const std::vector<Token>& tokens;
    int current = 0;

    // Helper functions
    bool match(TokenType type);
    bool check(TokenType type);
    Token advance();
    Token peek();
    Token previous();
    bool isAtEnd();
    Token consume(TokenType type, const std::string& message);

    // Parsing functions
    std::unique_ptr<FunctionDeclaration> function();
    std::unique_ptr<Statement> statement();
    std::unique_ptr<Statement> declaration();
    std::unique_ptr<Block> block();
    std::unique_ptr<IfStatement> ifStatement();
    std::unique_ptr<WhileStatement> whileStatement();
    std::unique_ptr<ReturnStatement> returnStatement();
    std::unique_ptr<Statement> expressionStatement();
    
    std::unique_ptr<Node> expression();
    std::unique_ptr<Node> equality();
    std::unique_ptr<Node> comparison();
    std::unique_ptr<Node> term();
    std::unique_ptr<Node> factor();
    std::unique_ptr<Node> primary();
};
