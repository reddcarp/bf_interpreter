#ifndef BF_INTERPRETER_TOKENIZE_HPP
#define BF_INTERPRETER_TOKENIZE_HPP

#include <string>

#include "token.hpp"

namespace bf_interpreter {

Token* tokenizeStream(std::istream &stream);

} // bf_interpreter


#endif