#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

bool needs_parens(Expr *e) {
	struct V : Expr::Visitor {
		bool r;
		void visit(Bool_expr *e) { r = false; }
	    void visit(And_expr *e) { r = true; }
	    void visit(AndThen_expr *e) { r = true; }
	    void visit(Or_expr *e) { r = true; }
	    void visit(OrElse_expr *e) { r = true; }
	    void visit(Xor_expr *e) { r = true; }
	    void visit(Not_expr *e) { r = true; }
	    void visit(Cond_expr *e) { r = true; }
	    void visit(Int_expr *e) { r = false; }
	    void visit(Negative_expr *e) { r = true; }
	    void visit(Equal_expr *e) { r = true; }
	    void visit(NotEqual_expr *e) { r = true; }
	    void visit(LessThan_expr *e) { r = true; }
	    void visit(GreaterThan_expr *e) { r = true; }
	    void visit(LessThanEqual_expr *e) { r = true; }
	    void visit(GreaterThanEqual_expr *e) { r = true; }
	    void visit(Add_expr *e) { r = false; }
	    void visit(Sub_expr *e) { r = false; }
	    void visit(Mult_expr *e) { r = true; }
	    void visit(Div_expr *e) { r = true; }
	    void visit(Rem_expr *e) { r = true; }
	    void visit(Ref_expr *e) { r = false; }
	    void visit(Val_expr *e) { r = false; }
	    void visit(Assign_expr *e) { r = false; }
	};
	V vis;
	e->accept(vis);
	return vis.r;
}

void print(Expr *e) {
	struct V : Expr::Visitor {
		void print_enclosed(Expr *e) {
			if (needs_parens(e)) {
				std::cout << "(";
				print(e);
				std::cout << ")";
			}
			else
				print(e);
		}

		void visit(Bool_expr *e) {
			if (e->getVal())
				std::cout << "true";
			else
				std::cout << "false";
		}
		void visit(And_expr *e) {
			print_enclosed(e->gete1());
			std::cout << " & ";
			print_enclosed(e->gete2());
		}
		void visit(AndThen_expr *e) {
			print_enclosed(e->gete1());
			std::cout << " && ";
			print_enclosed(e->gete2());
		}
		void visit(Or_expr *e) {
			print_enclosed(e->gete1());
			std::cout << " | ";
			print_enclosed(e->gete2());
		}
		void visit(OrElse_expr *e) {
			print_enclosed(e->gete1());
			std::cout << " || ";
			print_enclosed(e->gete2());
		}
		void visit(Xor_expr *e) {
			print_enclosed(e->gete1());
			std::cout << " ^ ";
			print_enclosed(e->gete2());
		}
		void visit(Not_expr *e) {
			std::cout << "!";
			print_enclosed(e->gete1());
		}
		void visit(Cond_expr *e) {
		    print_enclosed(e->gete1());
			std::cout << " ? ";
			print_enclosed(e->gete2());
			std::cout << " : ";
			print_enclosed(e->gete3());
		}
		void visit(Int_expr *e) {
            std::cout << e->getVal();
		}
		void visit(Negative_expr *e) {
            std::cout << "-";
            print_enclosed(e->gete1());
		}
		void visit(Equal_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " == ";
            print_enclosed(e->gete2());
		}
		void visit(NotEqual_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " != ";
            print_enclosed(e->gete2());
		}
		void visit(LessThan_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " < ";
            print_enclosed(e->gete2());
		}
		void visit(GreaterThan_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " > ";
            print_enclosed(e->gete2());
		}
		void visit(LessThanEqual_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " <= ";
            print_enclosed(e->gete2());
		}
		void visit(GreaterThanEqual_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " >= ";
            print_enclosed(e->gete2());
		}
		void visit(Add_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " + ";
            print_enclosed(e->gete2());
		}
		void visit(Sub_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " - ";
            print_enclosed(e->gete2());
		}
		void visit(Mult_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " * ";
            print_enclosed(e->gete2());
		}
		void visit(Div_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " / ";
            print_enclosed(e->gete2());
		}
		void visit(Rem_expr *e) {
            print_enclosed(e->gete1());
            std::cout << " % ";
            print_enclosed(e->gete2());
		}
		void visit(Ref_expr *e) {
            print_enclosed(e->getVal());
		}
	    void visit(Val_expr *e) {
            print_enclosed(e->getVal());
        }
	    void visit(Assign_expr *e) {
            print_enclosed(e->getVal());
	    }
	};
	V vis;
	e->accept(vis);
}

#endif
