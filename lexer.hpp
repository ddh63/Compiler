#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cstdlib>
#include "token.hpp"
#include "symbols.hpp"

class Lexer {
    std::string str;
    char *first, *last;
    std::string buf;
    const Keyword_table* kwt;
    Symbol_table* st;

    public:
    Lexer(const Keyword_table& kwt, Symbol_table& st, std::string& str) : str(str), kwt(&kwt), st(&st) {
        first = &str[0];
        last = &str[0] + str.size();
    }

    EOF() const { return first == last; }

    char lookahead() const { return EOF() ? 0 : *first; }

    char consume() {
        if (EOF())
            return 0;
        char c = *first++;
        buf.push_back(c);
        return c;
    }

    void ignore() { first++; }

    bool is_digit(char c) { return std::isdigit(c); }
    bool is_letter(char c) { return std::isalpha(c) || c == '_'; }
    bool is_letter_or_digit(char c) { return is_letter(c) || is_digit(c); }

    Token* integer() {
        assert(is_digit(lookahead()));

        consume();
        while (!EOF() && is_digit(lookahead()))
            consume();
        int n = std::atoi(buf.c_str());
        return new Int_token(Int_tok, n);
    }

    Token* word() {
        assert(is_letter(lookahead()));

        consume();
        while (!EOF() && is_letter_or_digit(lookahead()))
            consume();

        kwt->find(buf);
        auto i = kwt->find(buf);
        if (i != kwt->end()) {
            if (i->second == True_kw)
                return new Token(True_kw);
            if (i->second == False_kw)
                return new Token(False_kw);

            return new Token(i->second);
        }
    }

    Token* next();
};

Token* Lexer::next() {
    while (!EOF()) {
        buf.clear();
        switch (lookahead()) {
            case ' ':
            case '\n':
            case '\t': ignore(); continue;
            case '+': ignore(); return new Punc_token(Plus_tok);
            case '-': ignore(); return new Punc_token(Minus_tok);
            case '*': ignore(); return new Punc_token(Star_tok);
            case '/': ignore(); return new Punc_token(Slash_tok);
            case '%': ignore(); return new Punc_token(Percent_tok);
            case '&': {
                ignore();
                if (!EOF() && lookahead() == '&') {
                    ignore();
                    return new Punc_token(LogAmp_tok);
                }
                else {
                    return new Punc_token(Amp_tok);
                }
            }
            case '|': {
                ignore();
                if (!EOF() && lookahead() == '|') {
                    ignore();
                    return new Punc_token(LogPipe_tok);
                }
                else {
                    return new Punc_token(Pipe_tok);
                }
            }
            case '!': {
                ignore();
                if (!EOF() && lookahead() == '=') {
                    ignore();
                    return new Punc_token(NotEqual_tok);
                }
                else {
                    return new Punc_token(Bang_tok);
                }
            }
            case '=': {
                ignore();
                if (!EOF() && lookahead() == '=') {
                    ignore();
                    return new Punc_token(Equal_tok);
                }
                else {
                    assert(false && "= must have a = following it.");
                }
            }
            case '<': {
                ignore();
                if (!EOF() && lookahead() == '=') {
                    ignore();
                    return new Punc_token(Le_tok);
                }
                else {
                    return new Punc_token(Lt_tok);
                }
            }
            case '>': {
                ignore();
                if (!EOF() && lookahead() == '=') {
                    ignore();
                    return new Punc_token(Ge_tok);
                }
                else {
                    return new Punc_token(Gt_tok);
                }
            }
            case '?': ignore(); return new Punc_token(Question_tok);
            case ':': ignore(); return new Punc_token(Colon_tok);
            case '(': ignore(); return new Punc_token(LParen_tok);
            case ')': ignore(); return new Punc_token(RParen_tok);
            default: {
                if (is_digit(lookahead()))
                    return integer();
                else if (is_letter(lookahead()))
                    return word();
                else
                    throw std::runtime_error("Invalid character");
            }
        }
    }
    return new Punc_token(EOF_tok);
}

#endif // LEXER_HPP
