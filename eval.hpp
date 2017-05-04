#ifndef EVAL_HPP
#define EVAL_HPP

#include "ast.hpp"

int eval(Expr *e) {
	struct V : Expr::Visitor {
		int r;
		void visit(Bool_expr *e) { r = e->getVal(); }
		void visit(And_expr *e) { r = eval(e->gete1()) & eval(e->gete2()); }
		void visit(AndThen_expr *e) { r = eval(e->gete1()) && eval(e->gete2()); }
		void visit(Or_expr *e) { r = eval(e->gete1()) | eval(e->gete2()); }
		void visit(OrElse_expr *e) { r = eval(e->gete1()) || eval(e->gete2()); }
		void visit(Xor_expr *e) { r = eval(e->gete1()) ^ eval(e->gete2()); }
		void visit(Not_expr *e) { r = !eval(e->gete1()); }
		void visit(Cond_expr *e) { r = eval(e->gete1()) ? eval(e->gete2()) : eval(e->gete3()); }
		void visit(Int_expr *e) { r = e->getVal(); }
		void visit(Negative_expr *e) { r = 0 - eval(e->gete1()); }
		void visit(Equal_expr *e) { r = eval(e->gete1()) == eval(e->gete2()); }
		void visit(NotEqual_expr *e) { r = eval(e->gete1()) != eval(e->gete2()); }
		void visit(LessThan_expr *e) { r = eval(e->gete1()) < eval(e->gete2()); }
		void visit(GreaterThan_expr *e) { r = eval(e->gete1()) > eval(e->gete2()); }
		void visit(LessThanEqual_expr *e) { r = eval(e->gete1()) <= eval(e->gete2()); }
		void visit(GreaterThanEqual_expr *e) { r = eval(e->gete1()) >= eval(e->gete2()); }
		void visit(Add_expr *e) {
		    int a = eval(e->gete1());
		    int b = eval(e->gete2());
		    // Check for overflow
		    assert((a < INT_MAX - b) && "Addition overflow");
		    r = a + b;
        }
        void visit(Sub_expr *e) {
            int a = eval(e->gete1());
            int b = eval(e->gete2());
            r = a - b;
        }
        void visit(Mult_expr *e) {
            int a = eval(e->gete1());
            int b = eval(e->gete2());
            // Check for overflow
            if (a != 0)
                assert(((a * b) / a == b ) && "Multiplication overflow");
            r = a * b;
        }
        void visit(Div_expr *e) {
            int a = eval(e->gete1());
            int b = eval(e->gete2());
            // Check for overflow/undefined behavior
            if (a == INT_MIN && b == -1)
                assert(false && "Division overflow");
            if (b == INT_MIN)
                assert(false && "undefined behavior");
            if (b == 0)
                assert(false && "Divide by 0");
            r = a / b;
        }
        void visit(Rem_expr *e) {
            int a = eval(e->gete1());
            int b = eval(e->gete2());
            if (b == INT_MIN)
                assert(false && "Undefined behavior");
            if (b == 0)
                assert(false && "Mod by 0");
            r = a % b;
        }
        void visit(Ref_expr *e) {}
        void visit(Val_expr *e) {}
        void visit(Assign_expr *e) {}
	};

	V vis;
	e->accept(vis);
	return vis.r;
}

#endif
