#ifndef BF_INTERPRETER_TOKEN_HPP
#define BF_INTERPRETER_TOKEN_HPP

#include <iostream>
#include <memory>
#include <vector>

namespace bf_interpreter {

// Abstract classes

/**
 * @brief Represents a token in the BF interpreter.
 */
class Token {
 public:
    /**
     * @brief Constructs a new Token object with the specified character.
     * 
     * @param t The character representing the token.
     */
    explicit Token(char t);

    virtual ~Token() = default;

    /**
     * @brief Performs the action associated with the token.
     * 
     * @param data_index The current data index.
     * @param data The data vector.
     * @return A pointer to the next token to be executed.
     */
    virtual Token* action(size_t &data_index, std::vector<char> &data) = 0;

    std::unique_ptr<Token> next_token = nullptr; /* A pointer to the next token. */
    size_t repeated = 1; /* The number of times the token's action should be repeated. */
    const char token; /* The character representing the token. */
};

/**
 * @brief Represents a jump token in the BF interpreter.
 */
class JmpToken : public Token {
 public:
    /**
     * @brief Constructs a JmpToken object with the specified token character.
     * 
     * @param t The token character.
     */
    explicit JmpToken(char t);

    /**
     * @brief Returns the next token to execute based on the jump condition.
     * 
     * @param data_index The current data index.
     * @param data The data vector.
     * @return A pointer to the next token to execute.
     */
    Token* action(size_t &data_index, std::vector<char> &data) final;

    /**
     * @brief Checks the jump condition for the token.
     *
     * @param value The value at the current data index.
     * @return bool True if the jump condition is met, false otherwise.
     */
    virtual bool jmpCondition(int value) = 0;

    Token *jmp_to; /* The token to jump to. */
};
// ==============================================================

// Implemented Tokens

// Special Token, used to represent the beginning of the token linked-list
class StartToken : public Token {
 public:
    StartToken();
    Token* action(size_t &data_index, std::vector<char> &data) final;
};

// BF Token: `>`
class IncrementIndexToken : public Token {
 public:
    IncrementIndexToken();
    Token* action(size_t &data_index, std::vector<char> &data) final;
};

// BF Token: `<`
class DecrementIndexToken : public Token {
 public:
    DecrementIndexToken();
    Token* action(size_t &data_index, std::vector<char> &data) final;
};

// BF Token: `+`
class IncrementDataToken : public Token {
 public:
    IncrementDataToken();
    Token* action(size_t &data_index, std::vector<char> &data) final;
};

// BF Token: `-`
class DecrementDataToken : public Token {
 public:
    DecrementDataToken();
    Token* action(size_t &data_index, std::vector<char> &data) final;
};

// BF Token: '.'
class OutputDataToken : public Token {
 public:
    OutputDataToken();
    Token* action(size_t &data_index, std::vector<char> &data) final;
};

// BF Token: `,`
class InputDataToken : public Token {
 public:
    InputDataToken();
    Token* action(size_t &data_index, std::vector<char> &data) final;
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