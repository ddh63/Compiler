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
    Int_tok
};

class Token {
    int name;

	public:
    Token(int name) : name(name) {}
    int getName() { return name; }
    virtual int getVal() = 0;
	virtual ~Token() = default;
};

class Punc_token : public Token {
    public:
    Punc_token(int name) : Token(name) {}
    int getVal() { return getName(); }
};

class Bool_token : public Token {
    public:
    bool val;
    int getVal() { return val; }
};

class Int_token : public Token {
    public:
    int val;
    int getVal() { return val; }
    Int_token(int name, int val) : Token(name), val(val) {}
};

#endif // TOKEN_HPP
