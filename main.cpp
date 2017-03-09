#include <iostream>
#include "ast.hpp"
#include "eval.hpp"
#include "print.hpp"
#include "type.hpp"
#include "token.hpp"
#include "lexer.hpp"

#include <vector>

int main()
{
    std::string input;
    std::cout << "Input string: ";
    std::getline(std::cin, input);

    Lexer *lex = new Lexer(input);
    std::vector<Token*> tokens;
    while(Token* t = lex->next()) {
        tokens.push_back(t);
        if (t->getName() == EOF_tok) break;
    }

    std::cout << "Token types:\n";
    for (Token* token : tokens) {
        std::cout << token->getName();
        if (token->getName() == 21 || token->getName() == 22)
            std::cout << "\tValue: " << token->getVal();
        std::cout << "\n";
    }

    /*
    Context cxt;

    {
        Expr *E = new And_expr (
            new Bool_expr(true),
            new Bool_expr(true)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new AndThen_expr (
            new Bool_expr(true),
            new Bool_expr(true)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Or_expr(
            new Bool_expr(true),
            new Bool_expr(false)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new OrElse_expr(
            new Bool_expr(true),
            new Bool_expr(false)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Xor_expr(
            new Bool_expr(true),
            new Bool_expr(false)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Not_expr(
            new Bool_expr(false)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Cond_expr(
            new Bool_expr(true),
            new Int_expr(10),
            new Int_expr(20)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Equal_expr(
            new Int_expr(100),
            new Int_expr(100)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new NotEqual_expr(
            new Int_expr(100),
            new Int_expr(100)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new LessThan_expr(
            new Int_expr(50),
            new Int_expr(51)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new GreaterThan_expr(
            new Int_expr(50),
            new Int_expr(51)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new LessThanEqual_expr(
            new Int_expr(50),
            new Int_expr(50)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new GreaterThanEqual_expr(
            new Int_expr(50),
            new Int_expr(50)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Add_expr(
            new Int_expr(15000),
            new Int_expr(50000)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Sub_expr(
            new Int_expr(1500),
            new Int_expr(400)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Mult_expr(
            new Int_expr(10),
            new Int_expr(10)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Div_expr(
            new Int_expr(100),
            new Int_expr(10)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Rem_expr(
            new Int_expr(100),
            new Int_expr(9)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    {
        Expr *E = new Negative_expr(
            new Int_expr(100)
        );
        assert(check(cxt, E));
        print(E);
        std::cout << " == " << eval(E) << "\n";
    }
    */
    return 0;
}
