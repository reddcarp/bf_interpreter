#include <fstream>
#include <iostream>
#include <string>

#include "tokenize.hpp"

// TODO: Comment the code
// TODO: Cleanup the code

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./bf_interpreter <bf_filepath>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream fs(filename);

    if (!fs.is_open()) {
        std::cout << "Error: failed to open '" << filename << "'" << std::endl;
        return 1;
    }

    bf_interpreter::Token* head = nullptr;
    int return_code = 0;
    try {
        std::vector<char> data(10, 0);
        int data_index = 0;
        head = bf_interpreter::tokenizeStream(fs);
        bf_interpreter::Token* token = head->next_token;

        while (token != nullptr) {
            token = token->action(data_index, data);
        }
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return_code = 1;
    }

    // cleanup
    delete head;
    fs.close();

    return return_code;
}
