#ifndef DECLS_HPP
#define DECLS_HPP

#include "symbols.hpp"
#include "ast.hpp"

class Decl {
    virtual ~Decl() {}
};

class Var_decl {
    Expr* e1;
    symbol* name;

    public:
    Type* ty;
    Var_decl(symbol* s, Type* t) : name(s), ty(t), e1(nullptr) {}
};

#endif
