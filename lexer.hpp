#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cstdlib>
#include "token.hpp"

class Lexer {
    public:
    std::string str;
    unsigned int loc = 0;
    bool EOF = false;
    char *first, *last;
    std::string buf;

    Lexer(std::string str) : str(str) {
        first = &str.at(loc);
        last = &str[str.size()];
    }

    char lookahead() const {
        if (EOF)
            return 0;
        else
            return *first;
    }

    char consume() {
        if (EOF)
            return 0;
        buf += *first;
        if (loc < str.size() - 1)
            first = &str.at(++loc);
        else
            EOF = true;
        return buf.back();
    }

    char ignore() {
        if (loc < str.size() - 1) {
            first = &str.at(++loc);
            return *first;
        }
        else {
            EOF = true;
            return 0;
        }
    }

    Token* next();
};

Token* Lexer::next() {
    while (!EOF) {
        buf.clear();
        switch (lookahead()) {
            case '+': consume(); return new Punc_token(Plus_tok);
            case '-': consume(); return new Punc_token(Minus_tok);
            case '*': consume(); return new Punc_token(Star_tok);
            case '/': consume(); return new Punc_token(Slash_tok);
            case '%': consume(); return new Punc_token(Percent_tok);
            case '&': {
                consume();
                if (!EOF && lookahead() == '&') {
                    consume();
                    return new Punc_token(LogAmp_tok);
                }
                else {
                    return new Punc_token(Amp_tok);
                }
            }
            case '|': {
                consume();
                if (!EOF && lookahead() == '|') {
                    consume();
                    return new Punc_token(LogPipe_tok);
                }
                else {
                    return new Punc_token(Pipe_tok);
                }
            }
            case '!': {
                consume();
                if (!EOF && lookahead() == '=') {
                    consume();
                    return new Punc_token(NotEqual_tok);
                }
                else {
                    return new Punc_token(Bang_tok);
                }
            }
            case '=': {
                consume();
                if (!EOF && lookahead() == '=') {
                    consume();
                    return new Punc_token(Equal_tok);
                }
                else {
                    assert(false && "= must have a = following it.");
                }
            }
            case '<': {
                consume();
                if (!EOF && lookahead() == '=') {
                    consume();
                    return new Punc_token(Le_tok);
                }
                else {
                    return new Punc_token(Lt_tok);
                }
            }
            case '>': {
                consume();
                if (!EOF && lookahead() == '=') {
                    consume();
                    return new Punc_token(Ge_tok);
                }
                else {
                    return new Punc_token(Gt_tok);
                }
            }
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
                while (!EOF && std::isdigit(lookahead()))
                    consume();
                int n = std::atoi(buf.c_str());
                return new Int_token(Int_tok, n);
            }
            case 't': {
                consume();
                if (lookahead() == 'r') {
                    consume();
                    if (lookahead() == 'u') {
                        consume();
                        if (lookahead() == 'e') {
                            consume();
                            return new Bool_token(Bool_tok, true);
                        }
                    }
                }
                else {
                    assert(false && "Unknown string");
                }
            }
            case 'f': {
                consume();
                if (lookahead() == 'a') {
                    consume();
                    if (lookahead() == 'l') {
                        consume();
                        if (lookahead() == 's') {
                            consume();
                            if (lookahead() == 'e') {
                                consume();
                                return new Bool_token(Bool_tok, false);
                            }
                        }
                    }
                }
                else {
                    assert(false && "Unknown string");
                }
            }
            case ' ':
            case '\n':
            case '\t': ignore(); continue;
            default: assert(false && "Unknown value");
        }
    }
    return new Punc_token(EOF_tok);
}

#endif // LEXER_HPP
