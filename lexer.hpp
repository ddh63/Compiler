#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cstdlib>
#include "token.hpp"

class Lexer {
    public:
    std::string str;
    char *first, *last;
    std::string buf;

    Lexer(std::string str) : str(str) {
        first = &str.at(0);
        last = &str[str.size()];
    }

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
            case '+': consume(); return new Punc_token(Plus_tok);
            case '-': consume(); return new Punc_token(Minus_tok);
            case '*': consume(); return new Punc_token(Star_tok);
            case '/': consume(); return new Punc_token(Slash_tok);
            case '%': consume(); return new Punc_token(Percent_tok);
            case '&': // Need to check if &&
            case '|': // Need to check if ||
            case '!': // Need to check if !=
            case '=': // Need to check if ==
            case '<': // Need to check if <=
            case '>': // need to check if >=
            case '?': consume(); return new Punc_token(Question_tok);
            case ':': consume(); return new Punc_token(Colon_tok);
            case '(': consume(); return new Punc_token(LParen_tok);
            case ')': consume(); return new Punc_token(RParen_tok);
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                consume();
                while (!EOF() && std::isdigit(lookahead()))
                    consume();
                int n = std::atoi(buf.c_str());
                return new Int_token(Int_tok, n);
            }
            case ' ':
            case '\n':
            case '\t': consume(); continue;
        }
    }
    return nullptr;
}

#endif // LEXER_HPP
