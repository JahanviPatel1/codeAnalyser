#include "Parser.hpp"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::unique_ptr<Program> Parser::parse() {
    auto program = std::make_unique<Program>();
    while (!isAtEnd()) {
        program->functions.push_back(function());
    }
    return program;
}

std::unique_ptr<FunctionDeclaration> Parser::function() {
    // pattern: Type Identifier ( ) { ... }
    // Ideally we should parse global variables too, but let's assume functions only for now
    std::string type = consume(TokenType::KW_INT, "Expect return type (only int/void supported)").value; // Hack for now
    // Actually we should support int/void
    if (previous().type != TokenType::KW_INT && previous().type != TokenType::KW_VOID) {
        // Error
    }
    
    Token name = consume(TokenType::IDENTIFIER, "Expect function name.");
    consume(TokenType::LPAREN, "Expect '(' after function name.");
    consume(TokenType::RPAREN, "Expect ')' after parameters.");
    
    consume(TokenType::LBRACE, "Expect '{' before function body.");
    auto body = block();
    
    auto func = std::make_unique<FunctionDeclaration>();
    func->returnType = type;
    func->name = name.value;
    func->body = std::move(body);
    return func;
}

std::unique_ptr<Block> Parser::block() {
    auto node = std::make_unique<Block>();
    while (!check(TokenType::RBRACE) && !isAtEnd()) {
        node->statements.push_back(declaration());
    }
    consume(TokenType::RBRACE, "Expect '}' after block.");
    return node;
}

std::unique_ptr<Statement> Parser::declaration() {
    if (match(TokenType::KW_INT)) {
        // Variable declaration: int x = 5;
        Token name = consume(TokenType::IDENTIFIER, "Expect variable name.");
        std::unique_ptr<Node> initializer = nullptr;
        if (match(TokenType::EQUALS)) {
            initializer = expression();
        }
        consume(TokenType::SEMICOLON, "Expect ';' after variable declaration.");
        
        auto varDecl = std::make_unique<VariableDeclaration>();
        varDecl->type = "int";
        varDecl->name = name.value;
        varDecl->initializer = std::move(initializer);
        return varDecl;
    }
    return statement();
}

std::unique_ptr<Statement> Parser::statement() {
    if (match(TokenType::KW_IF)) return ifStatement();
    if (match(TokenType::KW_WHILE)) return whileStatement();
    if (match(TokenType::KW_RETURN)) return returnStatement();
    if (match(TokenType::LBRACE)) {
        // match() already consumed LBRACE
        return block();
    }
    return expressionStatement();
}

std::unique_ptr<IfStatement> Parser::ifStatement() {
    consume(TokenType::LPAREN, "Expect '(' after 'if'.");
    auto condition = expression();
    consume(TokenType::RPAREN, "Expect ')' after if condition.");
    
    auto thenBranch = statement();
    std::unique_ptr<Statement> elseBranch = nullptr;
    if (match(TokenType::KW_ELSE)) {
        elseBranch = statement();
    }
    
    auto stmt = std::make_unique<IfStatement>();
    stmt->condition = std::move(condition);
    stmt->thenBranch = std::move(thenBranch);
    stmt->elseBranch = std::move(elseBranch);
    return stmt;
}

std::unique_ptr<WhileStatement> Parser::whileStatement() {
    consume(TokenType::LPAREN, "Expect '(' after 'while'.");
    auto condition = expression();
    consume(TokenType::RPAREN, "Expect ')' after while condition.");
    auto body = statement();
    
    auto stmt = std::make_unique<WhileStatement>();
    stmt->condition = std::move(condition);
    stmt->body = std::move(body);
    return stmt;
}

std::unique_ptr<ReturnStatement> Parser::returnStatement() {
    std::unique_ptr<Node> value = nullptr;
    if (!check(TokenType::SEMICOLON)) {
        value = expression();
    }
    consume(TokenType::SEMICOLON, "Expect ';' after return value.");
    
    auto stmt = std::make_unique<ReturnStatement>();
    stmt->value = std::move(value);
    return stmt;
}

std::unique_ptr<Statement> Parser::expressionStatement() {
    auto expr = expression();
    consume(TokenType::SEMICOLON, "Expect ';' after expression.");
    auto stmt = std::make_unique<ExpressionStatement>();
    stmt->expression = std::move(expr);
    return stmt;
}

// Expression Parsing (Recursive Descent Precedence)

std::unique_ptr<Node> Parser::expression() {
    return equality();
}

std::unique_ptr<Node> Parser::equality() {
    auto expr = comparison();
    while (match(TokenType::EQ_EQ) || match(TokenType::BANG_EQ)) {
        Token op = previous();
        auto right = comparison();
        auto binExpr = std::make_unique<BinaryExpression>();
        binExpr->left = std::move(expr);
        binExpr->op = op.value;
        binExpr->right = std::move(right);
        expr = std::move(binExpr);
    }
    return expr;
}

std::unique_ptr<Node> Parser::comparison() {
    auto expr = term();
    while (match(TokenType::GT) || match(TokenType::GT_EQ) || match(TokenType::LT) || match(TokenType::LT_EQ)) {
        Token op = previous();
        auto right = term();
        auto binExpr = std::make_unique<BinaryExpression>();
        binExpr->left = std::move(expr);
        binExpr->op = op.value;
        binExpr->right = std::move(right);
        expr = std::move(binExpr);
    }
    return expr;
}

std::unique_ptr<Node> Parser::term() {
    auto expr = factor();
    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        Token op = previous();
        auto right = factor();
        auto binExpr = std::make_unique<BinaryExpression>();
        binExpr->left = std::move(expr);
        binExpr->op = op.value;
        binExpr->right = std::move(right);
        expr = std::move(binExpr);
    }
    return expr;
}

std::unique_ptr<Node> Parser::factor() {
    auto expr = primary();
    while (match(TokenType::SLASH) || match(TokenType::STAR)) {
        Token op = previous();
        auto right = primary();
        auto binExpr = std::make_unique<BinaryExpression>();
        binExpr->left = std::move(expr);
        binExpr->op = op.value;
        binExpr->right = std::move(right);
        expr = std::move(binExpr);
    }
    return expr;
}

std::unique_ptr<Node> Parser::primary() {
    if (match(TokenType::NUMBER)) {
        auto lit = std::make_unique<Literal>();
        lit->value = previous().value;
        return lit;
    }
    if (match(TokenType::STRING_LITERAL)) {
        auto lit = std::make_unique<Literal>();
        lit->value = "\"" + previous().value + "\"";
        return lit;
    }
    if (match(TokenType::IDENTIFIER)) {
        auto id = std::make_unique<Identifier>();
        id->name = previous().value;
        return id;
    }
    if (match(TokenType::LPAREN)) {
        auto expr = expression();
        consume(TokenType::RPAREN, "Expect ')' after expression.");
        return expr;
    }
    
    // Error
    std::cerr << "Error: Unexpected token " << peek().toString() << " at primary expression." << std::endl;
    // Return dummy to not crash immediately
    return std::make_unique<Literal>(); 
}

// Helpers

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current - 1];
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) return advance();
    std::cerr << "Parser Error: " << message << " Found: " << peek().toString() << std::endl;
    // Simplistic error handling
    return peek();
}
