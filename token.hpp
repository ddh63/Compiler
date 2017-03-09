#ifndef TOKEN_HPP
#define TOKEN_HPP

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
    Bool_tok
};

class Token {
    token_kind name;

	public:
    Token(token_kind name) : name(name) {}
    token_kind getName() { return name; }
    virtual int getVal() = 0;
	virtual ~Token() = default;
};

class Punc_token : public Token {
    public:
    int getVal() { return 0; }
    Punc_token(token_kind name) : Token(name) {}
};

class Bool_token : public Token {
    public:
    int val;
    int getVal() { return val; }
    Bool_token(token_kind name, bool val) : Token(name), val(val) {}
};

class Int_token : public Token {
    public:
    int val;
    int getVal() { return val; }
    Int_token(token_kind name, int val) : Token(name), val(val) {}
};

#endif // TOKEN_HPP
