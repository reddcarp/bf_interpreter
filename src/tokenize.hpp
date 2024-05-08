#ifndef BF_INTERPRETER_TOKENIZE_HPP
#define BF_INTERPRETER_TOKENIZE_HPP

#include <memory>

#include "token.hpp"

namespace bf_interpreter {

std::unique_ptr<Token> tokenizeStream(std::istream &stream);

} // bf_interpreter


#endif