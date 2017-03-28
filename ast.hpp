#ifndef AST_HPP
#define AST_HPP

#include <cassert>

class Bool_type;
class Int_type;

class Bool_expr;
class And_expr;
class AndThen_expr;
class Or_expr;
class OrElse_expr;
class Xor_expr;
class Not_expr;
class Cond_expr;

class Int_expr;
class Negative_expr;
class Equal_expr;
class NotEqual_expr;
class LessThan_expr;
class GreaterThan_expr;
class LessThanEqual_expr;
class GreaterThanEqual_expr;
class Add_expr;
class Sub_expr;
class Mult_expr;
class Div_expr;
class Rem_expr;

class Type {
	struct Visitor;

	public:
	virtual ~Type() = default;
	virtual void accept(Visitor&) {}
};

class Bool_type : public Type {};
class Int_type : public Type {};

class Expr {
	public:
    Type* ty;
    struct Visitor;
	virtual ~Expr() = default;
	virtual void accept(Visitor&) = 0;
};

struct Expr::Visitor {
	virtual void visit(Bool_expr*) = 0;
	virtual void visit(And_expr*) = 0;
	virtual void visit(AndThen_expr*) = 0;
	virtual void visit(Or_expr*) = 0;
	virtual void visit(OrElse_expr*) = 0;
	virtual void visit(Xor_expr*) = 0;
	virtual void visit(Not_expr*) = 0;
	virtual void visit(Cond_expr*) = 0;
	virtual void visit(Int_expr*) = 0;
	virtual void visit(Negative_expr*) = 0;
	virtual void visit(Equal_expr*) = 0;
	virtual void visit(NotEqual_expr*) = 0;
	virtual void visit(LessThan_expr*) = 0;
	virtual void visit(GreaterThan_expr*) = 0;
	virtual void visit(LessThanEqual_expr*) = 0;
	virtual void visit(GreaterThanEqual_expr*) = 0;
	virtual void visit(Add_expr*) = 0;
	virtual void visit(Sub_expr*) = 0;
	virtual void visit(Mult_expr*) = 0;
	virtual void visit(Div_expr*) = 0;
	virtual void visit(Rem_expr*) = 0;
};

class Bool_expr : public Expr {
	bool value;

	public:
	Bool_expr(bool v) : value(v) {}
	bool getVal() { return value; }
	void accept(Visitor& v) { return v.visit(this); }
};

class And_expr : public Expr {
	Expr *e1;
	Expr *e2;

	public:
	And_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
	Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
	void accept(Visitor& v) { return v.visit(this); }
};

class AndThen_expr : public Expr {
	Expr *e1;
	Expr *e2;

	public:
	AndThen_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
	Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
	void accept(Visitor& v) { return v.visit(this); }
};

class Or_expr : public Expr {
	Expr *e1;
	Expr *e2;

	public:
	Or_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
	Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
	void accept(Visitor& v) { return v.visit(this); }
};

class OrElse_expr : public Expr {
	Expr *e1;
	Expr *e2;

	public:
	OrElse_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
	Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
	void accept(Visitor& v) { return v.visit(this); }
};

class Xor_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    Xor_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Not_expr : public Expr {
	Expr *e1;

	public:
	Not_expr(Expr *e1) : e1(e1) {}
	Expr* gete1() { return e1; }
	void accept(Visitor& v) { return v.visit(this); }
};

class Cond_expr : public Expr {
	Expr *e1;
	Expr *e2;
	Expr *e3;

	public:
	Cond_expr(Expr *e1, Expr *e2, Expr *e3) : e1(e1), e2(e2), e3(e3) {}
	Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
	Expr* gete3() { return e3; }
	void accept(Visitor& v) { return v.visit(this); }
};

class Int_expr : public Expr {
    int value;

    public:
    Int_expr(int v) : value(v) {}
    int getVal() { return value; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Negative_expr : public Expr {
    Expr *e1;

    public:
    Negative_expr(Expr *e1) : e1(e1) {}
    Expr* gete1() { return e1; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Equal_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    Equal_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class NotEqual_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    NotEqual_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class LessThan_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    LessThan_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class GreaterThan_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    GreaterThan_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class LessThanEqual_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    LessThanEqual_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class GreaterThanEqual_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    GreaterThanEqual_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
	Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Add_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    Add_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
    Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Sub_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    Sub_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
    Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Mult_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    Mult_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
    Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Div_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    Div_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
    Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Rem_expr : public Expr {
    Expr *e1;
    Expr *e2;

    public:
    Rem_expr(Expr *e1, Expr *e2) : e1(e1), e2(e2) {}
    Expr* gete1() { return e1; }
    Expr* gete2() { return e2; }
    void accept(Visitor& v) { return v.visit(this); }
};

class Context {
    public:
	Bool_type bool_type;
	Int_type int_type;
};

#endif
