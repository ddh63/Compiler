#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "ast.hpp"
#include "symbols.hpp"

class Translator {

    public:
    Translator(Context& cxt) : cxt(&cxt) {}

    Expr* onAdd(Expr* e1, Expr* e2) {
        Add_expr* a = new Add_expr(e1, e2);
        a->ty = check(*cxt, a);
        return a;
    }
    Expr* onSub(Expr* e1, Expr* e2) {
        Sub_expr* s = new Sub_expr(e1, e2);
        s->ty = check(*cxt, s);
        return s;
    }
    Expr* onMul(Expr* e1, Expr* e2) {
        Mult_expr* m = new Mult_expr(e1, e2);
        m->ty = check(*cxt, m);
        return m;
    }
    Expr* onDiv(Expr* e1, Expr* e2) {
        Div_expr* d = new Div_expr(e1, e2);
        d->ty = check(*cxt, d);
        return d;
    }
    Expr* onRem(Expr* e1, Expr* e2) {
        Rem_expr* r = new Rem_expr(e1, e2);
        r->ty = check(*cxt, r);
        return r;
    }
    Expr* onNeg(Expr* e1) {
        Negative_expr* n = new Negative_expr(e1);
        n->ty = check(*cxt, n);
        return n;
    }
    Expr* onTrue(Token* t) {
        Bool_expr* b = new Bool_expr(true);
        b->ty = check(*cxt, b);
        return b;
    }
    Expr* onFalse(Token* t) {
        Bool_expr* b = new Bool_expr(false);
        b->ty = check(*cxt, b);
        return b;
    }
    Expr* onInt(Token* t) {
        Int_token* val = static_cast<Int_token*>(t);
        Int_expr* i = new Int_expr(val->getVal());
        i->ty = check(*cxt, i);
        return i;
    }

    Context* cxt;
};

#endif // TRANSLATOR_HPP
