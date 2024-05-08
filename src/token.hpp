// what we need
// a reference to the current data pointer index // index
// a reference to the data 
#ifndef BF_INTERPRETER_TOKEN_HPP
#define BF_INTERPRETER_TOKEN_HPP

#include <vector>
#include <iostream>

namespace bf_interpreter {

// Abstract classes
class Token {
 public:
    explicit Token(char t);
    virtual ~Token();

    virtual Token* action(int &data_index, std::vector<char> &data) = 0;
    Token *next_token = nullptr;
    size_t repeated = 1;
    const char token;
};

class JmpToken : public Token {
 public:
    explicit JmpToken(char t);

    Token* action(int &data_index, std::vector<char> &data) final;
    virtual bool jmpCondition(int value) = 0;

    Token *jmp_to;
};
// ==============================================================

// Special Token, used to represent the beginning of the token linked-list
class StartToken : public Token {
 public:
    StartToken() : Token(' ') {}
    Token* action(int &data_index, std::vector<char> &data) final { return next_token; }
};

// Implemented Tokens
// BF Token: `>`
class IncrementIndexToken : public Token {
 public:
    IncrementIndexToken();
    Token* action(int &data_index, std::vector<char> &data) final;
};

// BF Token: `<`
class DecrementIndexToken : public Token {
 public:
    DecrementIndexToken();
    Token* action(int &data_index, std::vector<char> &data) final;
};

// BF Token: `+`
class IncrementDataToken : public Token {
 public:
    IncrementDataToken();
    Token* action(int &data_index, std::vector<char> &data) final;
};

// BF Token: `-`
class DecrementDataToken : public Token {
 public:
    DecrementDataToken();
    Token* action(int &data_index, std::vector<char> &data) final;
};

// BF Token: '.'
class OutputDataToken : public Token {
 public:
    OutputDataToken();
    Token* action(int &data_index, std::vector<char> &data) final;
};

// BF Token: `,`
class InputDataToken : public Token {
 public:
    InputDataToken();
    Token* action(int &data_index, std::vector<char> &data) final;
};

// BF Token: `[`
class JmpIfZeroToken : public JmpToken {
 public:
    JmpIfZeroToken();
    bool jmpCondition(int value) final;
};

// BF Token: `]`
class JmpIfNotZeroToken : public JmpToken {
 public:
    JmpIfNotZeroToken();
    bool jmpCondition(int value) final;
};
// ==============================================================

} // bf_interpreter

#endif