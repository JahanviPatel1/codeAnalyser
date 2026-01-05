#pragma once
#include <string>
#include <vector>
#include "Token.hpp"

class Lexer {
public:
    explicit Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    int pos;
    int line;
    int length;

    char peek(int offset = 0) const;
    char advance();
    bool isAtEnd() const;
    void skipWhitespace();

    Token makeToken(TokenType type, std::string value);
    Token scanToken();
    Token identifier();
    Token number();
    Token stringLiteral();
};
