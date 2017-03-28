#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"

#include <vector>

class Parser {
    std::vector<Token*> tokens;

    public:
    Parser(std::vector<Token*> t) : tokens(t) {}

    bool EOF() { return tokens.empty(); }

    Token* peek() {
        if (!EOF())
            return tokens.front();
        else
            return nullptr;
    }

    token_kind lookahead() {
        Token* t = peek();
        return t->getName();
    }

    Token* consume() {
        assert(!EOF());

        Token* t = tokens.front();
        tokens.erase(tokens.begin());

        return t;
    }
};

#endif // PARSER_HPP
