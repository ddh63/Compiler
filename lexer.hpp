#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include "token.hpp"

class Lexer {
    public:
    char *first, *last;
    std::string buf;

    bool EOF() const { return first == last; }

    char lookahead() const {
        if (EOF())
            return 0;
        else
            return *first;
    }

    char consume() {
        if (EOF())
            return 0;
        buf += *first++;
        return buf.back();
    }

    char ignore() { return EOF() ? 0 : *first++; }

    Token* next();
};


Token* Lexer::next() {
    while (!EOF()) {
        buf.clear();
        switch (lookahead()) {
            case '(': consume(); return new Punc_token(LParen_tok);
            case ' ':
            case '\n':
            case '\t': consume(); continue;
        }
    }
    return nullptr;
}

#endif // LEXER_HPP
