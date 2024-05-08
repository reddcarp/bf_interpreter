#include <cstdio>
#include <iostream>
#include <stdexcept>

#include "token.hpp"

constexpr char BACKSPACE_VALUE = 10;

namespace bf_interpreter {

Token::Token(char t)
: token(t)
{}

IncrementIndexToken::IncrementIndexToken() : Token('>') {}
Token* IncrementIndexToken::action(int &data_index, std::vector<char> &data) {
    data_index += repeated;
    size_t data_size = data.size();

    // expending vector if it is too small
    for (size_t i = data_index; i > data_size; i--) {
        data.emplace_back(0);
    }
    return next_token.get();
}

DecrementIndexToken::DecrementIndexToken() : Token('<') {}
Token* DecrementIndexToken::action(int &data_index, std::vector<char> &data) {
    data_index -= repeated;

    if (data_index < 0) {
        throw std::underflow_error("Error: Trying to access index < 0");
    }

    return next_token.get();
}

IncrementDataToken::IncrementDataToken() : Token('+') {}
Token* IncrementDataToken::action(int &data_index, std::vector<char> &data) {
    data[data_index] += repeated;
    return next_token.get();
}

DecrementDataToken::DecrementDataToken() : Token('-') {}
Token* DecrementDataToken::action(int &data_index, std::vector<char> &data) {
    data[data_index] -= repeated;
    return next_token.get();
}

OutputDataToken::OutputDataToken() : Token('.') {}
Token* OutputDataToken::action(int &data_index, std::vector<char> &data) {
    for (size_t i = 0; i < repeated; i++) {
        std::cout << data[data_index];
    }

    return next_token.get();
}

// TODO: change acquisition of input to be more robust
// idea: only accept one character at a time
// and discard the rest
InputDataToken::InputDataToken() : Token(',') {}
Token* InputDataToken::action(int &data_index, std::vector<char> &data) {
    std::cout << "Enter a character: ";
    char input = BACKSPACE_VALUE;

    // this allows us to have two input requests in a row
    // without the backspace from the previous command
    // affecting the following one
    while (input == BACKSPACE_VALUE) {
        input = std::getchar();
    }
    data[data_index] = input;

    return next_token.get();
}

JmpToken::JmpToken(char t) : Token(t) {}
Token* JmpToken::action(int &data_index, std::vector<char> &data) {
    if (jmpCondition(data[data_index])) {
        return jmp_to->next_token.get();
    }
    return next_token.get();
}

JmpIfZeroToken::JmpIfZeroToken() : JmpToken('[') {}
bool JmpIfZeroToken::jmpCondition(int value) {
    return value == 0;
}

JmpIfNotZeroToken::JmpIfNotZeroToken() : JmpToken(']') {}
bool JmpIfNotZeroToken::jmpCondition(int value) {
    return value != 0;
}

} // bf_interpreter