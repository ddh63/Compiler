#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "ast.hpp"
#include "symbols.hpp"

class Translator() {

    public:
    translator(Context& cxt) : cxt(&cxt) {}

    Expr* onAdd(Expr* e1, Expr* e2);
    Expr* onSub(Expr* e1, Expr* e2);
    Expr* onMul(Expr* e1, Expr* e2);
    Expr* onDiv(Expr* e1, Expr* e2);
    Expr* onRem(Expr* e1, Expr* e2);
    Expr* onNeg(Expr* e1);
    Expr* onBool(Token* t);
    Expr* onInt(Token* t);

    Context* cxt;
};

#endif // TRANSLATOR_HPP
