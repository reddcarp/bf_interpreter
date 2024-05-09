#include <cstdio>
#include <iostream>
#include <stdexcept>

#include "token.hpp"

namespace bf_interpreter {

Token::Token(char t)
: token(t)
{}

StartToken::StartToken() : Token(' ') {}
Token* StartToken::action(size_t &data_index, std::vector<char> &data) {
    return next_token.get();
}

IncrementIndexToken::IncrementIndexToken() : Token('>') {}
Token* IncrementIndexToken::action(size_t &data_index, std::vector<char> &data) {
    data_index += repeated;
    size_t data_size = data.size();

    // expending vector if it is too small
    for (size_t i = data_index; i > data_size; i--) {
        data.emplace_back(0);
    }
    return next_token.get();
}

DecrementIndexToken::DecrementIndexToken() : Token('<') {}
Token* DecrementIndexToken::action(size_t &data_index, std::vector<char> &data) {
    if (data_index < repeated) {
        throw std::underflow_error("Error: Trying to access index < 0");
    }

    data_index -= repeated;
    return next_token.get();
}

IncrementDataToken::IncrementDataToken() : Token('+') {}
Token* IncrementDataToken::action(size_t &data_index, std::vector<char> &data) {
    data[data_index] += repeated;
    return next_token.get();
}

DecrementDataToken::DecrementDataToken() : Token('-') {}
Token* DecrementDataToken::action(size_t &data_index, std::vector<char> &data) {
    data[data_index] -= repeated;
    return next_token.get();
}

OutputDataToken::OutputDataToken() : Token('.') {}
Token* OutputDataToken::action(size_t &data_index, std::vector<char> &data) {
    for (size_t i = 0; i < repeated; i++) {
        std::cout << data[data_index];
    }

    return next_token.get();
}

InputDataToken::InputDataToken() : Token(',') {}
Token* InputDataToken::action(size_t &data_index, std::vector<char> &data) {
    std::cout << "Enter a character: ";

    int input = std::getchar();
    if (input == EOF) {
        throw std::invalid_argument("Error: EOF reached while trying to get input");
    }

    data[data_index] = static_cast<char>(input);

    // discarding the rest of the input if the user entered more than one character
    if (input != '\n') {
        int trash;
        while ((trash = std::getchar()) != '\n' && trash != EOF);
    }

    return next_token.get();
}

JmpToken::JmpToken(char t) : Token(t) {}
Token* JmpToken::action(size_t &data_index, std::vector<char> &data) {
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