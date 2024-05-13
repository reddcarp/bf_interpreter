#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

void readChar(const size_t &data_index, std::vector<char> &data) {
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
}

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

    const auto filecontent = std::string(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
    std::size_t fsize = filecontent.size();
    fs.close();

    std::stack<size_t> jpm_start_stack;
    size_t i = 0;

    size_t data_index = 0;
    std::vector<char> data(10, 0);


    while (i < fsize) {
        switch (filecontent[i]) {
            case '>':
                data_index++;
                if (data_index == data.size()) {
                    data.push_back(0);
                }
                break;
            case '<':
                if (data_index == 0) {
                    std::cerr << "Error: Trying to access index < 0" << std::endl;
                    return 1;
                }
                data_index--;
                break;
            case '+':
                data[data_index]++;
                break;
            case '-':
                data[data_index]--;
                break;
            case '.':
                std::cout << data[data_index];
                break;
            case ',':
                readChar(data_index, data);
                break;
            case '[':
                if (data[data_index] == 0) {
                    i++;
                    size_t balance_counter = 0;
                    while (i < fsize && (filecontent[i] != ']' || balance_counter != 0)) {
                        if (filecontent[i] == '[') {
                            balance_counter++;
                        }
                        else if (filecontent[i] == ']') {
                            balance_counter--;
                        }
                        i++;
                    }
                    if (i >= fsize) {
                        std::cerr << "Error: missing corresponding `]`" << std::endl;
                        return 1;
                    }
                }
                else {
                    jpm_start_stack.push(i);
                }
                break;
            case ']':
                if (jpm_start_stack.empty()) {
                    std::cerr << "Error: missing corresponding `[`" << std::endl;
                    return 1;
                }

                if (data[data_index] != 0) {
                    i = jpm_start_stack.top();
                }
                else {
                    jpm_start_stack.pop();
                }

                break;
            default:
                break;
        }
        i++;
    }

    if (!jpm_start_stack.empty()) {
        std::cerr << "Error: missing corresponding `]`" << std::endl;
        return 1;
    }

    return 0;
}
