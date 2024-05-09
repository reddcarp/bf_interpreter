#include <fstream>
#include <iostream>
#include <string>

#include "tokenize.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./bf_interpreter <bf_filepath>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream fs(filename);
    if (!fs.is_open()) {
        std::cerr << "Error: failed to open '" << filename << "'" << std::endl;
        return 1;
    }

    int return_code = 0;
    try {
        std::unique_ptr<bf_interpreter::Token> head = bf_interpreter::tokenizeStream(fs);
        bf_interpreter::Token* token = head->next_token.get();

        size_t data_index = 0;
        std::vector<char> data(10, 0);
        while (token != nullptr) {
            token = token->action(data_index, data);
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return_code = 1;
    }

    fs.close();
    return return_code;
}
