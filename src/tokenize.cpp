#include <format>
#include <stack>

#include "tokenize.hpp"

namespace bf_interpreter {

static Token* createAndLinkJmpTokens(::std::stack<Token *>& jpm_starts) {
    auto jmp_start_token = static_cast<JmpToken *>(jpm_starts.top());
    jpm_starts.pop();

    auto jmp_end = new JmpIfNotZeroToken();
    jmp_end->jmp_to = jmp_start_token;
    jmp_start_token->jmp_to = jmp_end;

    return jmp_end;
}

template <typename TokenCreate>
static void handleRepeatableToken(Token *&cur, char c, TokenCreate createToken) {
    static_assert(std::is_invocable_r_v<Token *, TokenCreate>);
    if (cur->token == c) {
        cur->repeated += 1;
    }
    else {
        cur->next_token = createToken();
        cur = cur->next_token;
    }
}

Token* tokenizeStream(std::istream &stream) {
    Token *head = new StartToken();
    Token *cur = head;
    std::stack<Token *> jpm_starts;

    char c;
    while (stream.get(c)) {
        switch(c) {
            case '<':
                handleRepeatableToken(cur, '<', []() { return new DecrementIndexToken(); });
                break;
            case '>':
                handleRepeatableToken(cur, '>', []() { return new IncrementIndexToken(); });
                break;
            case '+':
                handleRepeatableToken(cur, '+', []() { return new IncrementDataToken(); });
                break;
            case '-':
                handleRepeatableToken(cur, '-', []() { return new DecrementDataToken(); });
                break;
            case '.':
                handleRepeatableToken(cur, '.', []() { return new OutputDataToken(); });
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
                    throw std::format_error("Error: missing corresponding `[`");
                }

                cur->next_token = createAndLinkJmpTokens(jpm_starts);
                cur = cur->next_token;
                break;
            default:
                break;
        }
    }

    if (!jpm_starts.empty()) {
        delete head;
        throw std::format_error("Error: missing corresponding `]`");
    }

    return head;
}

} // bf_interpreter