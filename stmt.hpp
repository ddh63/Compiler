#ifndef STMT_HPP
#define STMT_HPP

#include "ast.hpp"
#include <vector>

class Stmt {
    public:
    virtual ~Stmt() = default;
};

class Expr_stmt : public Stmt {
    public:
    Expr* e1;
    Expr_stmt(Expr* e1) : e1(e1) {}
};

class Decl_stmt : public Stmt {
    public:
    Decl* dec;
    Decl_stmt(Decl* d) : dec(d) {}
    Decl* getDecl() { return dec; }
};


// Decl
class Decl {
    public:
    virtual ~Decl() {}
};

class Var_decl : public Decl {
    Expr* e1;
    symbol* name;

    public:
    Type* ty;
    Var_decl(symbol* s, Type* t) : e1(nullptr), name(s), ty(t) {}
    void setVar(Expr* e) {
        if (e1 != nullptr)
            throw std::runtime_error("Variable initialized already\n");
        else
            e1 = e;
    }
};

class Program_decl : public Decl {
    std::vector<Stmt*> seq;

    public:
    Program_decl(std::vector<Stmt*> s) : seq(s) {}
    std::vector<Stmt*>& getSeq() { return seq; }
};

#endif
