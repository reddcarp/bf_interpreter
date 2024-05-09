#include <format>
#include <stack>

#include "tokenize.hpp"

namespace bf_interpreter {

static std::unique_ptr<Token> createAndLinkJmpTokens(std::stack<JmpIfZeroToken *> &jpm_starts) {
    auto jmp_start_token = jpm_starts.top();
    jpm_starts.pop();

    auto jmp_end = std::make_unique<JmpIfNotZeroToken>();
    jmp_end->jmp_to = jmp_start_token;
    jmp_start_token->jmp_to = jmp_end.get();

    return jmp_end;
}

template <typename TokenCreate>
static void handleRepeatableToken(Token *&cur, char c, TokenCreate createToken) {
    static_assert(std::is_invocable_r_v<std::unique_ptr<Token>, TokenCreate>);
    if (cur->token == c) {
        cur->repeated += 1;
    }
    else {
        cur->next_token = createToken();
        cur = cur->next_token.get();
    }
}

std::unique_ptr<Token> tokenizeStream(std::istream &stream) {
    auto head = std::make_unique<StartToken>();
    Token *cur = head.get();
    std::stack<JmpIfZeroToken *> jpm_starts;

    char c;
    while (stream.get(c)) {
        switch(c) {
            case '<':
                handleRepeatableToken(cur, c, []() { return std::make_unique<DecrementIndexToken>(); });
                break;
            case '>':
                handleRepeatableToken(cur, c, []() { return std::make_unique<IncrementIndexToken>(); });
                break;
            case '+':
                handleRepeatableToken(cur, c, []() { return std::make_unique<IncrementDataToken>(); });
                break;
            case '-':
                handleRepeatableToken(cur, c, []() { return std::make_unique<DecrementDataToken>(); });
                break;
            case '.':
                handleRepeatableToken(cur, c, []() { return std::make_unique<OutputDataToken>(); });
                break;
            case ',':
                cur->next_token = std::make_unique<InputDataToken>();
                cur = cur->next_token.get();
                break;
            case '[':
                cur->next_token = std::make_unique<JmpIfZeroToken>();
                cur = cur->next_token.get();
                jpm_starts.push(static_cast<JmpIfZeroToken *>(cur));
                break;
            case ']':
                if (jpm_starts.empty()) {
                    throw std::format_error("Error: missing corresponding `[`");
                }

                cur->next_token = createAndLinkJmpTokens(jpm_starts);
                cur = cur->next_token.get();
                break;
            default:
                break;
        }
    }

    if (!jpm_starts.empty()) {
        throw std::format_error("Error: missing corresponding `]`");
    }

    return head;
}

} // bf_interpreter