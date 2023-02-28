#include "text_editor.h"

int main(int argc, char** argv) {
    int return_value = 0;

    if (argc != 2) {
        std::cout << "Invalid number of arguments. " << std::endl;
        return_value = 1;
    }

    if (return_value == 0) {
        TextEditor editor;
        bool program_exit = false;
        std::cout << editor.read_or_create_file(argv[1]);

        while (!program_exit) {
            std::string line;

            std::cout << editor.print_lines();
            std::getline(std::cin, line);
            std::cin.clear();

            std::string command_output = editor.perform_command(line);

            if (command_output == "EXIT") {
                program_exit = true;
            } else if (!command_output.empty()) {
                std::cout << command_output;
            }
        }
        editor.write_to_file();
    }

    return return_value;
}