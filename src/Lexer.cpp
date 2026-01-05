#include "Lexer.hpp"
#include <cctype>
#include <unordered_map>

Lexer::Lexer(const std::string& source) : source(source), pos(0), line(1), length(source.length()) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd()) break;
        tokens.push_back(scanToken());
    }
    tokens.push_back(makeToken(TokenType::END_OF_FILE, ""));
    return tokens;
}

char Lexer::peek(int offset) const {
    if (pos + offset >= length) return '\0';
    return source[pos + offset];
}

char Lexer::advance() {
    if (isAtEnd()) return '\0';
    return source[pos++];
}

bool Lexer::isAtEnd() const {
    return pos >= length;
}

void Lexer::skipWhitespace() {
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\r' || c == '\t') {
            advance();
        } else if (c == '\n') {
            line++;
            advance();
        } else {
            break;
        }
    }
}

Token Lexer::makeToken(TokenType type, std::string value) {
    return {type, value, line};
}

Token Lexer::scanToken() {
    char c = advance();

    // Identifiers
    if (isalpha(c) || c == '_') {
        pos--; // backtrack to include first char
        return identifier();
    }
    
    // Numbers
    if (isdigit(c)) {
        pos--;
        return number();
    }

    switch (c) {
        case '(': return makeToken(TokenType::LPAREN, "(");
        case ')': return makeToken(TokenType::RPAREN, ")");
        case '{': return makeToken(TokenType::LBRACE, "{");
        case '}': return makeToken(TokenType::RBRACE, "}");
        case ';': return makeToken(TokenType::SEMICOLON, ";");
        case ',': return makeToken(TokenType::COMMA, ",");
        case '+': return makeToken(TokenType::PLUS, "+");
        case '-': return makeToken(TokenType::MINUS, "-");
        case '*': return makeToken(TokenType::STAR, "*");
        case '/': 
            if (peek() == '/') {
                // Comment
                while (peek() != '\n' && !isAtEnd()) advance();
                // We stopped at newline.
                // Restart scanning (which includes skipping whitespace)
                // But we are inside scanToken which doesn't skip whitespace at start usually?
                // Actually, the main loop calls skipWhitespace. 
                // We should just return a recursive call, but ensuring we are in a valid state.
                // The issue was scanToken() assumes it starts on a valid char.
                // But we are at \n.
                skipWhitespace(); 
                return scanToken(); 
            }
            return makeToken(TokenType::SLASH, "/");
        case '=': return (peek() == '=') ? (advance(), makeToken(TokenType::EQ_EQ, "==")) : makeToken(TokenType::EQUALS, "=");
        case '!': return (peek() == '=') ? (advance(), makeToken(TokenType::BANG_EQ, "!=")) : makeToken(TokenType::UNKNOWN, "!");
        case '<': return (peek() == '=') ? (advance(), makeToken(TokenType::LT_EQ, "<=")) : makeToken(TokenType::LT, "<");
        case '>': return (peek() == '=') ? (advance(), makeToken(TokenType::GT_EQ, ">=")) : makeToken(TokenType::GT, ">");
        case '&': if(peek() == '&') { advance(); return makeToken(TokenType::AND, "&&"); } break;
        case '|': if(peek() == '|') { advance(); return makeToken(TokenType::OR, "||"); } break;
        case '"': return stringLiteral();
    }

    return makeToken(TokenType::UNKNOWN, std::string(1, c));
}

Token Lexer::identifier() {
    int start = pos;
    while (!isAtEnd() && (isalnum(peek()) || peek() == '_')) {
        advance();
    }
    std::string text = source.substr(start, pos - start);
    
    // Check keywords
    if (text == "if") return makeToken(TokenType::KW_IF, text);
    if (text == "else") return makeToken(TokenType::KW_ELSE, text);
    if (text == "while") return makeToken(TokenType::KW_WHILE, text);
    if (text == "for") return makeToken(TokenType::KW_FOR, text);
    if (text == "return") return makeToken(TokenType::KW_RETURN, text);
    if (text == "int") return makeToken(TokenType::KW_INT, text);
    if (text == "void") return makeToken(TokenType::KW_VOID, text);
    
    return makeToken(TokenType::IDENTIFIER, text);
}

Token Lexer::number() {
    int start = pos;
    while (!isAtEnd() && isdigit(peek())) {
        advance();
    }
    return makeToken(TokenType::NUMBER, source.substr(start, pos - start));
}

Token Lexer::stringLiteral() {
    int start = pos; // points to char after leading "
    while (!isAtEnd() && peek() != '"') {
        advance();
    }
    if (isAtEnd()) {
        // Unterminated string
        return makeToken(TokenType::UNKNOWN, "Unterminated String");
    }
    
    // The previous advance consumed content, now consume the closing quote
    std::string value = source.substr(start, pos - start);
    advance(); // consume closing "
    return makeToken(TokenType::STRING_LITERAL, value);
}
