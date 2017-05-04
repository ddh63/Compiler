#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "ast.hpp"
#include "symbols.hpp"
#include "stmt.hpp"
#include "scope.hpp"
#include <vector>

class Translator {

    public:
    Translator(Context& cxt) : cxt(&cxt) {}
    Context* cxt;
    Scope s;
    std::unordered_map<Decl*, Expr*> mapToVal;

    Expr* onCond(Expr* e1, Expr* e2, Expr* e3) {
        Cond_expr* c = new Cond_expr(e1, e2, e3);
        c->ty = check(*cxt, c);
        return c;
    }

    Expr* onLogOr(Expr* e1, Expr* e2) {
        OrElse_expr* o = new OrElse_expr(e1, e2);
        o->ty = check(*cxt, o);
        return o;
    }

    Expr* onLogAnd(Expr* e1, Expr* e2) {
        AndThen_expr* a = new AndThen_expr(e1, e2);
        a->ty = check(*cxt, a);
        return a;
    }

    Expr* onEqual(Expr* e1, Expr* e2) {
        Equal_expr* e = new Equal_expr(e1, e2);
        e->ty = check(*cxt, e);
        return e;
    }

    Expr* onNotEqual(Expr* e1, Expr* e2) {
        NotEqual_expr* n = new NotEqual_expr(e1, e2);
        n->ty = check(*cxt, n);
        return n;
    }

    Expr* onLt(Expr* e1, Expr* e2) {
        LessThan_expr* l = new LessThan_expr(e1, e2);
        l->ty = check(*cxt, l);
        return l;
    }

    Expr* onGt(Expr* e1, Expr* e2) {
        GreaterThan_expr* g = new GreaterThan_expr(e1, e2);
        g->ty = check(*cxt, g);
        return g;
    }

    Expr* onLe(Expr* e1, Expr* e2) {
        LessThanEqual_expr* l = new LessThanEqual_expr(e1, e2);
        l->ty = check(*cxt, l);
        return l;
    }

    Expr* onGe(Expr* e1, Expr* e2) {
        GreaterThanEqual_expr* g = new GreaterThanEqual_expr(e1, e2);
        g->ty = check(*cxt, g);
        return g;
    }

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

    Type* onBoolTy() {
        return &cxt->bool_type;
    }

    Type* onIntTy() {
        return &cxt->int_type;
    }

    symbol* onId(Token* t) {
        Id_token* id = static_cast<Id_token*>(t);
        return id->getSymbol();
    }

    Decl* onProgram(std::vector<Stmt*> s) {
        return new Program_decl(s);
    }

    Stmt* onDeclarationStatement(Decl* d) {
        return new Decl_stmt(d);
    }

    Stmt* onExpressionStatement(Expr* e) {
        return new Expr_stmt(e);
    }

    Decl* onVariableDeclaration(Type* ty, symbol* name) {
        Var_decl* v = new Var_decl(name, ty);
        if (s.insert(name, v))
            return v;
        else
            throw std::runtime_error("Variable name already in use\n");
    }

    Decl* onVariableCreation(Type* ty, Decl* d, Expr* e) {
        Var_decl* v = static_cast<Var_decl*>(d);
        v->ty = ty;
        v->setVar(e);
        mapToVal.insert({d, e});
        return v;
    }

};
#endif // TRANSLATOR_HPP
