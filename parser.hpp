#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"
#include "translator.hpp"
#include "stmt.hpp"

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
        return conditionalExpression();
    }

    Expr* conditionalExpression() {
        Expr *e1 = logicalOrExpression();
        while (true) {
            if (match_if(Question_tok)) {
                Expr *e2 = expression();
                match(Colon_tok);
                Expr *e3 = expression();
                e1 = tran.onCond(e1, e2, e3);
            }
            else
                break;
        }
        return e1;
    }

    Expr* logicalOrExpression() {
        Expr *e1 = logicalAndExpression();
        while (true) {
            if (match_if(LogPipe_tok)) {
                Expr *e2 = logicalAndExpression();
                e1 = tran.onLogOr(e1, e2);
            }
            else
                break;
        }
        return e1;
    }

    Expr* logicalAndExpression() {
        Expr *e1 = equalityExpression();
        while (true) {
            if (match_if(LogAmp_tok)) {
                Expr *e2 = equalityExpression();
                e1 = tran.onLogAnd(e1, e2);
            }
            else
                break;
        }
        return e1;
    }

    Expr* equalityExpression() {
        Expr *e1 = orderingExpression();
        while (true) {
            if (match_if(Equal_tok)) {
                Expr *e2 = orderingExpression();
                e1 = tran.onEqual(e1, e2);
            }
            else if (match_if(NotEqual_tok)) {
                Expr *e2 = orderingExpression();
                e1 = tran.onNotEqual(e1, e2);
            }
            else
                break;
        }
        return e1;
    }

    Expr* orderingExpression() {
        Expr *e1 = additiveExpression();
        while (true) {
            if (match_if(Lt_tok)) {
                Expr *e2 = additiveExpression();
                e1 = tran.onLt(e1, e2);
            }
            else if (match_if(Gt_tok)) {
                Expr *e2 = additiveExpression();
                e1 = tran.onGt(e1, e2);
            }
            else if (match_if(Le_tok)) {
                Expr *e2 = additiveExpression();
                e1 = tran.onLe(e1, e2);
            }
            else if (match_if(Ge_tok)) {
                Expr *e2 = additiveExpression();
                e1 = tran.onGe(e1, e2);
            }
            else
                break;
        }
        return e1;
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

    Decl* program() {
        std::vector<Stmt*> seq;
        while (tokens.front()->getName() != EOF_tok) {
            seq.push_back(statement());
        }
        return tran.onProgram(seq);
    }

    Stmt* statement() {
        switch (lookahead()) {
            case Var_kw: return declarationStatement();
            default: return expressionStatement();
        }
    }

    Stmt* declarationStatement() {
        Decl* d = declaration();
        return tran.onDeclarationStatement(d);
    }

    Stmt* expressionStatement() {
        Expr* e = expression();
        match(Semicolon_tok);
        return tran.onExpressionStatement(e);
    }

    Decl* declaration() {
        if (lookahead() == Var_kw)
            return variableDeclaration();
        else
            throw std::runtime_error("Wrong declaration\n");
    }

    Decl* variableDeclaration() {
        consume();

        Type* ty = getType();
        symbol* name = getId();
        Decl* v = tran.onVariableDeclaration(ty, name);
        match(Assign_tok);
        Expr* e = expression();

        tran.onVariableCreation(ty, v, e);
        match(Semicolon_tok);
        return v;
    }

    Type* getType() {
        switch (lookahead()) {
            case Bool_kw:
                consume();
                return tran.onBoolTy();
            case Int_kw:
                consume();
                return tran.onIntTy();
            default: throw std::runtime_error("Expected type keyword\n");
        }
    }

    symbol* getId() {
        Token* tok = match(Id_tok);
        return tran.onId(tok);
    }

};

#endif // PARSER_HPP
