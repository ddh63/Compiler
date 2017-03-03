#ifndef TOKEN_HPP
#define TOKEN_HPP

enum token_kind {
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
	virtual ~Token() = default;
};

class Punc_token : public Token {};

class Bool_token : public Token {
    bool val;
};

class Int_token : public Token {
    int val;
};

#endif // TOKEN_HPP
