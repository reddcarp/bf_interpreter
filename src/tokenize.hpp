#ifndef BF_INTERPRETER_TOKENIZE_HPP
#define BF_INTERPRETER_TOKENIZE_HPP

#include <memory>

#include "token.hpp"

namespace bf_interpreter {

/**
 * Tokenizes the input stream and returns a unique pointer to a Token object.
 *
 * @param stream The input stream to tokenize.
 * @return A unique pointer to a Token object representing the tokenized stream.
 */
std::unique_ptr<Token> tokenizeStream(std::istream &stream);

} // bf_interpreter


#endif