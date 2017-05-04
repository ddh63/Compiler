#ifndef TYPE_HPP
#define TYPE_HPP

#include "ast.hpp"
#include <iostream>
#include <stdexcept>

Type* check(Context& cxt, Expr* e) {
    struct V : Expr::Visitor {
        Context& cxt;
        Type* t;
        V(Context& c) : cxt(c) {}
        void visit(Bool_expr* e) {
            t = &cxt.bool_type;
        }
        void visit(And_expr* e) {
            // Check if e1 and e2 are bool
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression 1 not of type bool");
            assert(check(cxt, e->gete2()) == &cxt.bool_type && "Expression 2 not of type bool");
            t = &cxt.bool_type;
        }
        void visit(AndThen_expr* e) {
            // Check if e1 and e2 are bool
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression 1 not of type bool");
            assert(check(cxt, e->gete2()) == &cxt.bool_type && "Expression 2 not of type bool");
            t = &cxt.bool_type;
        }
        void visit(Or_expr* e) {
            // Check if e1 and e2 are bool
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression 1 not of type bool");
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression 2 not of type bool");
            t = &cxt.bool_type;
        }
        void visit(OrElse_expr* e) {
            // Check if e1 and e2 are bool
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression 1 not of type bool");
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression 2 not of type bool");
            t = &cxt.bool_type;
        }
        void visit(Xor_expr* e) {
            // Check if e1 and e2 are bool
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression 1 not of type bool");
            assert(check(cxt, e->gete2()) == &cxt.bool_type && "Expression 2 not of type bool");
            t = &cxt.bool_type;
        }
        void visit(Not_expr* e) {
            // Check if e1 is bool
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression not of type bool");
            t = &cxt.bool_type;
        }
        void visit(Cond_expr* e) {
            // Check if e1 is bool
            // Check if e2 and e3 are same type
            assert(check(cxt, e->gete1()) == &cxt.bool_type && "Expression not of type bool");
            assert(check(cxt, e->gete2()) == check(cxt, e->gete3()) && "Expression 2 and 3 must have same type");
            t = check(cxt, e->gete2());
        }
        void visit(Int_expr* e) {
            t = &cxt.int_type;
        }
        void visit(Negative_expr* e) {
            // Check e1 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression not of type int");
            t = &cxt.int_type;
        }
        void visit(Equal_expr* e) {
            // Check e1 type == e2 type
            assert(check(cxt, e->gete1()) == check(cxt, e->gete2()) && "Equal expression must have two expressions of same type");
            t = &cxt.bool_type;
        }
        void visit(NotEqual_expr* e) {
            // Check e1 type == e2 type
            assert(check(cxt, e->gete1()) == check(cxt, e->gete2()) && "Not Equal expression must have two expressions of same type");
            t = &cxt.bool_type;
        }
        void visit(LessThan_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(GreaterThan_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(LessThanEqual_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(GreaterThanEqual_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(Add_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(Sub_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(Mult_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(Div_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(Rem_expr* e) {
            // Check e1 type == int
            // Check e2 type == int
            assert(check(cxt, e->gete1()) == &cxt.int_type && "Expression 1 not of type int");
            assert(check(cxt, e->gete2()) == &cxt.int_type && "Expression 2 not of type int");
            t = &cxt.int_type;
        }
        void visit(Ref_expr* e) {
            if (check(cxt, e->getVal()) == &cxt.int_type)
                t = &cxt.int_type;
            else if (check(cxt, e->getVal()) == &cxt.bool_type)
                t = &cxt.bool_type;
            else
                throw std::runtime_error("Invalid type\n");
        }
        void visit(Val_expr* e) {
            if (check(cxt, e->getVal()) == &cxt.int_type)
                t = &cxt.int_type;
            else if (check(cxt, e->getVal()) == &cxt.bool_type)
                t = &cxt.bool_type;
            else
                throw std::runtime_error("Invalid type\n");
        }
        void visit(Assign_expr* e) {
            if (check(cxt, e->getVal()) == &cxt.int_type)
                t = &cxt.int_type;
            else if (check(cxt, e->getVal()) == &cxt.bool_type)
                t = &cxt.bool_type;
            else
                throw std::runtime_error("Invalid type\n");
        }
    };
    V vis(cxt);
    e->accept(vis);
    return vis.t;
}

#endif // TYPE_HPP
