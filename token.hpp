#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <unordered_map>
#include "symbols.hpp"

enum token_kind {
    EOF_tok,
    Plus_tok,
    Minus_tok,
    Star_tok,       // Mult
    Slash_tok,      // Div
    Percent_tok,    // Mod
    Amp_tok,
    LogAmp_tok,
    Pipe_tok,
    LogPipe_tok,
    Bang_tok,       // Not
    Equal_tok,
    NotEqual_tok,
    Lt_tok,
    Le_tok,
    Gt_tok,
    Ge_tok,
    Question_tok,
    Colon_tok,
    LParen_tok,
    RParen_tok,
    Int_tok,
    Id_tok,

    Bool_kw,
    Int_kw,
    True_kw,
    False_kw
};

class Keyword_table : public std::unordered_map<std::string, token_kind> {
    public:
    Keyword_table() {
        insert({"bool", Bool_kw});
        insert({"int", Int_kw});
        insert({"true", True_kw});
        insert({"false", False_kw});
    }
};

class Token {
    token_kind name;

	public:
    Token(token_kind name) : name(name) {}
    token_kind getName() { return name; }
	virtual ~Token() = default;
};

class Punc_token : public Token {
    public:
    Punc_token(token_kind name) : Token(name) {}
};

class Int_token : public Token {
    int val;

    public:
    int getVal() { return val; }
    Int_token(token_kind name, int val) : Token(name), val(val) {}
};

class Id_token : public Token {
    symbol* sym;

    public:
    std::string getSymbol() { return *sym; }
    Id_token(token_kind name, symbol* s) : Token(name), sym(s) {}
};

#endif // TOKEN_HPP
