#pragma once
#include <string>
#include <iostream>

enum class TokenType {
    // Keywords
    KW_IF, KW_ELSE, KW_WHILE, KW_FOR, KW_RETURN, KW_INT, KW_VOID,
    
    // Identifiers & Literals
    IDENTIFIER, NUMBER, STRING_LITERAL,
    
    // Operators
    PLUS, MINUS, STAR, SLASH, EQUALS, 
    EQ_EQ, BANG_EQ, LT, GT, LT_EQ, GT_EQ,
    AND, OR,
    
    // Delimiters
    LPAREN, RPAREN, LBRACE, RBRACE, SEMICOLON, COMMA,
    
    // End of File
    END_OF_FILE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    
    std::string typeToString() const {
        switch(type) {
            case TokenType::KW_IF: return "KW_IF";
            case TokenType::KW_ELSE: return "KW_ELSE";
            case TokenType::KW_WHILE: return "KW_WHILE";
            case TokenType::KW_FOR: return "KW_FOR";
            case TokenType::KW_RETURN: return "KW_RETURN";
            case TokenType::KW_INT: return "KW_INT";
            case TokenType::KW_VOID: return "KW_VOID";
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::NUMBER: return "NUMBER";
            case TokenType::STRING_LITERAL: return "STRING";
            case TokenType::PLUS: return "PLUS";
            case TokenType::MINUS: return "MINUS";
            case TokenType::STAR: return "STAR";
            case TokenType::SLASH: return "SLASH";
            case TokenType::EQUALS: return "ASSIGN";
            case TokenType::EQ_EQ: return "EQ_EQ";
            case TokenType::BANG_EQ: return "NEQ";
            case TokenType::LT: return "LT";
            case TokenType::GT: return "GT";
            case TokenType::LT_EQ: return "LTE";
            case TokenType::GT_EQ: return "GTE";
            case TokenType::AND: return "AND";
            case TokenType::OR: return "OR";
            case TokenType::LPAREN: return "LPAREN";
            case TokenType::RPAREN: return "RPAREN";
            case TokenType::LBRACE: return "LBRACE";
            case TokenType::RBRACE: return "RBRACE";
            case TokenType::SEMICOLON: return "SEMICOLON";
            case TokenType::COMMA: return "COMMA";
            case TokenType::END_OF_FILE: return "EOF";
            default: return "UNKNOWN";
        }
    }

    std::string toString() const {
        return "Token(" + typeToString() + ", '" + value + "', Line:" + std::to_string(line) + ")";
    }
};

inline std::ostream& operator<<(std::ostream& os, const Token& token) {
    return os << token.toString();
}
