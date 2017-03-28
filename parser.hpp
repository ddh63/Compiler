#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"
#include "translator.hpp"

#include <vector>

class Parser {
    std::vector<Token*> tokens;

    public:
    Parser(std::vector<Token*> t, Context& cxt) : tokens(t), tran(cxt) {}

    Translator tran;

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

    Token* require(token_kind tk) {
        assert(lookahead() == tk);
        return consume();
    }

    Token* match(token_kind tk) {
        if (lookahead() == tk)
            return consume();
        else
            throw std::runtime_error("Expected token kind " + tk);
    }

    Token* match_if(token_kind tk) {
        if (lookahead() == tk)
            return consume();
        else
            return nullptr;
    }

    Expr* expression() {
        return additiveExpression();
    }

    Expr* additiveExpression() {
        Expr *e1 = multiplicativeExpression();
        while (true) {
            if (match_if(Plus_tok)) {
                Expr *e2 = multiplicativeExpression();
                e1 = tran.onAdd(e1, e2);
            }
            else if (match_if(Minus_tok)) {
                Expr *e2 = multiplicativeExpression();
                e1 = tran.onSub(e1, e2);
            }
            else
                break;
        }
        return e1;
    }

    Expr* multiplicativeExpression() {
        Expr *e1 = unaryExpression();
        while (true) {
            if (match_if(Star_tok)) {
                Expr *e2 = unaryExpression();
                e1 = tran.onMul(e1, e2);
            }
            else if (match_if(Slash_tok)) {
                Expr *e2 = unaryExpression();
                e1 = tran.onDiv(e1, e2);
            }
            else if (match_if(Percent_tok)) {
                Expr *e2 = unaryExpression();
                e1 = tran.onRem(e1, e2);
            }
            else
                break;
        }
        return e1;
    }

    Expr* unaryExpression() {
        if (match_if(Minus_tok)) {
            Expr *e1 = unaryExpression();
            return tran.onNeg(e1);
        }
        else
            return primaryExpression();
    }

    Expr* primaryExpression() {
        switch (lookahead()) {
            case True_kw: return tran.onTrue(consume());
            case False_kw: return tran.onFalse(consume());
            case Int_tok: return tran.onInt(consume());
            case LParen_tok: {
                consume();
                Expr *e1 = expression();
                match(RParen_tok);
                return e1;
            }
            default: {
                throw std::runtime_error("Invalid expression");
                break;
            }
        }
    }

};

#endif // PARSER_HPP
