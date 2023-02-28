//
// Created by Jack MacKinnon on 2023-01-20.
//

#include "text_editor.h"

TextEditor::TextEditor() :m_list() {}

// purpose: returns the first word or letter in the input buffer
std::string TextEditor::get_command_letter(std::stringstream &input_line) {
    std::string return_string;
    input_line >> return_string;
    return return_string;
}

// trys to output the numbers in the input buffer and if it fails sets the
// values to -1
void TextEditor::get_command_numbers(std::stringstream& input_line,
                                     int *start_num, int *end_num) {
    input_line >> *start_num;

    if (!input_line) {
        *start_num = INVALID_NUMBER_DEFAULT;
        *end_num = INVALID_NUMBER_DEFAULT;
    } else {
        input_line >> *end_num;
        if (!input_line) {
            *end_num = INVALID_NUMBER_DEFAULT;
        }
    }
}

// purpose: format the text with the appropriate line number
void TextEditor::format_line_number(std::stringstream& output, int line_number,
                                    const std::string& text) {
    output << line_number << ">" << text << "\n";
}

// purpose: to take in two numbers and determine if they are greater than 0
// and less than the total number of nodes in the linked list
bool TextEditor::is_valid_input(int first_num, int second_num) {
    return (first_num > 0 && second_num < m_list.get_node_count());
}

// purpose: take in a line of text from the user and test it against the rules
// set to determine if it is a valid command
bool TextEditor::is_valid_command(std::string &user_input, int word_count,
                                  int start_num, int end_num) {
    bool return_value = false;

    // if the word count is 4 or more it means it cannot be a command
    if (word_count >= 4) {
        return_value = false;
    } else if (user_input == LIST_COMMAND || user_input == DELETE_COMMAND) {
        if (word_count == 3) {
            return_value = (is_valid_input(start_num, end_num - 1)
                            && start_num < end_num);
        } else {
            return_value = (word_count == 1) ||
                           is_valid_input(start_num, start_num - 1);
        }
    } else if (user_input == INPUT_COMMAND && word_count <= 2) {
        return_value = (word_count == 1 && m_line_number > 1) ||
                       (is_valid_input(start_num, start_num - 2));
    } else if (user_input == EXIT_COMMAND && word_count == 1) {
        return_value = true;
    }

    return return_value;
}

void TextEditor::perform_input_command(int start_num, int word_count) {
    if (word_count == 2) {
        m_line_number = start_num;
    } else {
        m_line_number--;
    }
}

void TextEditor::perform_list_command(int start_num, int end_num,
                                      std::stringstream &output, int word_count) {
    if (word_count == 3) {
        for (int i = (start_num - 1); i < end_num; i++) {
            format_line_number(output, i + 1, m_list[i]);
        }
    } else if (word_count == 2) {
        format_line_number(output, start_num, m_list[start_num - 1]);
    } else {
        for (int i = 0; i < m_list.get_node_count(); i++) {
            format_line_number(output, i + 1, m_list[i]);
        }
    }
}

void TextEditor::perform_delete_command(int start_num, int end_num, int word_count) {

    if (word_count == 3) {
        int reduce_line_number = 0;
        for (int i = (start_num - 1); i < end_num; i++) {
            m_list.remove(start_num - 1);
            if (i < m_line_number) {reduce_line_number++;}
        }
        m_line_number -= reduce_line_number;
    } else if (word_count == 2) {
        m_list.remove(start_num - 1);
        m_line_number--;
    } else {
        if (m_line_number <= m_list.get_node_count()) {
            m_list.remove(m_line_number - 1);
            m_line_number--;
        }
    }
}

std::string TextEditor::read_or_create_file(const std::string &file_path) {
    m_file_path = file_path;
    m_line_number = 1;

    std::stringstream return_value;
    std::ifstream input_file(file_path);

    // if file has failed to open, then the file does not exist and will
    // then create the file
    if (!input_file.fail()) {
        std::string line;
        while (!input_file.eof()) {
            // each line in the file will be added as a node to the linked list
            std::getline(input_file, line);
            m_list.add(line);
            return_value << m_line_number << ">" << line << "\n";
            m_line_number++;
        }
    } else {
        // creates the file if it does not open
        std::ofstream create_file(file_path);
    }

    return return_value.str();
}

void TextEditor::write_to_file() {
    // check to ensure there is a file path currently
    if (m_file_path.empty()) {
        return;
    }

    std::ofstream output(m_file_path, std::ios::trunc);
    if (!output.fail()) {
        output << m_list;
    }
}

std::string TextEditor::print_lines() const {
    return std::to_string(m_line_number) + ">";
}

void TextEditor::count_words(const std::string& line_to_count, int &word_count) {
    if (word_count == 0) {
        std::stringstream temp_text_stream(line_to_count);
        std::string temp_word;

        while (std::getline(temp_text_stream, temp_word, ' ')) {
            if (++word_count == 4) {
                break;
            }
        }
    }
}

std::string TextEditor::perform_command(std::string& user_input) {
    std::stringstream return_value, input_line_buffer;
    input_line_buffer << user_input;

    std::string check_command = get_command_letter(input_line_buffer);
    int word_count = 0;
    count_words(user_input, word_count);
    int start_number, end_number;

    // if second and third input are anything other than numbers, the values of
    // start_number and end_number will change to -1
    get_command_numbers(input_line_buffer, &start_number, &end_number);

    if (is_valid_command(check_command, word_count, start_number, end_number)) {

        if (check_command == EXIT_COMMAND) {
            return_value << "EXIT";
        } else if (check_command == INPUT_COMMAND) {
            perform_input_command(start_number, word_count);
        } else if (check_command == LIST_COMMAND) {
            perform_list_command(start_number, end_number, return_value, word_count);
        } else if (check_command == DELETE_COMMAND) {
            perform_delete_command(start_number, end_number, word_count);
        }
    } else {
        m_list.insert_before(user_input, m_line_number - 1);
        m_line_number++;
    }

    return return_value.str();
}