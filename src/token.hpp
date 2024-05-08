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
    Token(char t);
    // Easy to forget, the destructor is virtual to ensure proper cleanup
    // it makes it so the proper destructor are called in the derived class
    // otherwise, only this base destructor would be called
    virtual ~Token();

    virtual Token* action(int &data_index, ::std::vector<char> &data) = 0;
    Token *next_token;
    size_t repeated;
    const char token;
};

class JmpToken : public Token {
 public:
    JmpToken(char t);

    Token* action(int &data_index, ::std::vector<char> &data);
    virtual bool jmpCondition(int value) = 0;

    Token *jmp_to;
};
// ==============================================================

// Special Token, used to represent the beginning of the token linked-list
class StartToken : public Token {
 public:
    StartToken() : Token(' ') {}
    virtual Token* action(int &data_index, ::std::vector<char> &data) { return next_token; }
};

// Implemented Tokens
// BF Token: `>`
class IncrementIndexToken : public Token {
 public:
    IncrementIndexToken();
    virtual Token* action(int &data_index, ::std::vector<char> &data);
};

// BF Token: `<`
class DecrementIndexToken : public Token {
 public:
    DecrementIndexToken();
    virtual Token* action(int &data_index, ::std::vector<char> &data); 
};

// BF Token: `+`
class IncrementDataToken : public Token {
 public:
    IncrementDataToken();
    virtual Token* action(int &data_index, ::std::vector<char> &data);
};

// BF Token: `-`
class DecrementDataToken : public Token {
 public:
    DecrementDataToken();
    virtual Token* action(int &data_index, ::std::vector<char> &data);
};

// BF Token: '.'
class OutputDataToken : public Token {
 public:
    OutputDataToken();
    virtual Token* action(int &data_index, ::std::vector<char> &data);
};

// BF Token: `,`
class InputDataToken : public Token {
 public:
    InputDataToken();
    virtual Token* action(int &data_index, ::std::vector<char> &data);
};

// BF Token: `[`
class JmpIfZeroToken : public JmpToken {
 public:
    JmpIfZeroToken();
    virtual bool jmpCondition(int value);
};

// BF Token: `]`
class JmpIfNotZeroToken : public JmpToken {
 public:
    JmpIfNotZeroToken();
    virtual bool jmpCondition(int value);
};
// ==============================================================

} // bf_interpreter

#endif