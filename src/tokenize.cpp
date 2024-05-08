#include <stack>
#include <stdexcept>

#include "tokenize.hpp"

namespace bf_interpreter {

Token* tokenizeStream(::std::istream &stream) {
    Token *head = new StartToken();
    Token *cur = head;
    ::std::stack<Token *> jpm_starts;

    char c;
    while (stream.get(c)) {
        switch(c) {
            case '<':
                if (cur->token == '<') {
                    cur->repeated += 1;
                }
                else {
                    cur->next_token = new DecrementIndexToken();
                    cur = cur->next_token;
                }
                break;
            case '>':
                if (cur->token == '>') {
                    cur->repeated += 1;
                }
                else {
                    cur->next_token = new IncrementIndexToken();
                    cur = cur->next_token;
                }
                break;
            case '+':
                if (cur->token == '+') {
                    cur->repeated += 1;
                }
                else {
                    cur->next_token = new IncrementDataToken();
                    cur = cur->next_token;
                }
                break;
            case '-':
                if (cur->token == '-') {
                    cur->repeated += 1;
                }
                else {
                    cur->next_token = new DecrementDataToken();
                    cur = cur->next_token;
                }
                break;
            case '.':
                if (cur->token == '.') {
                    cur->repeated += 1;
                }
                else {
                    cur->next_token = new OutputDataToken();
                    cur = cur->next_token;
                }
                break;
            case ',':
                cur->next_token = new InputDataToken();
                cur = cur->next_token;
                break;
            case '[':
                cur->next_token = new JmpIfZeroToken();
                cur = cur->next_token;
                jpm_starts.push(cur);
                break;
            case ']':
                if (jpm_starts.empty()) {
                    delete head;
                    throw ::std::logic_error("Error: missing corresponding `[`");
                }

                // scoped so the locally defined variables are not accessible outside of this case
                {
                    // static_cast since we already know the type of objects in jmp_starts
                    auto jmp_start_token = static_cast<JmpToken *>(jpm_starts.top());
                    jpm_starts.pop();
                    auto jmp_end = new JmpIfNotZeroToken();
                    jmp_end->jmp_to = jmp_start_token;
                    jmp_start_token->jmp_to = jmp_end;

                    cur->next_token = jmp_end;
                }
                cur = cur->next_token;
                break;
            default:
                break;
        }
    }

    if (!jpm_starts.empty()) {
        delete head;
        throw ::std::logic_error("Error: missing corresponding `]`");
    }

    return head;
}

} // bf_interpreter