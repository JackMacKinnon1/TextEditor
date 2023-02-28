//
// Created by Jack MacKinnon on 2023-01-20.
//

#ifndef ASSIGNMENT1_TEXT_EDITOR_H
#define ASSIGNMENT1_TEXT_EDITOR_H
#include "linked_list.h"
#include <fstream>
#include <sstream>

class TextEditor {
private:

    LinkedList m_list{};
    std::string m_file_path;
    int m_line_number {0};

    const std::string EXIT_COMMAND = "E";
    const std::string INPUT_COMMAND = "I";
    const std::string DELETE_COMMAND = "D";
    const std::string LIST_COMMAND = "L";
    static const int INVALID_NUMBER_DEFAULT = -1;

    static std::string get_command_letter(std::stringstream& input_line);
    static void get_command_numbers(std::stringstream& input_line,
                                    int *start_num, int *end_num);
    static void format_line_number(std::stringstream& output, int line_number,
                                   const std::string& text);
    bool is_valid_input(int first_num, int second_num);
    bool is_valid_command(std::string& user_input, int word_count,
                                 int start_num, int end_num);
    void perform_input_command(int start_num, int word_count);
    void perform_list_command(int start_num, int end_num,
                              std::stringstream& output, int word_count);
    void perform_delete_command(int start_num, int end_num, int word_count);
public:
    // constructors
    TextEditor();

    // object methods
    std::string read_or_create_file(const std::string& file_path);
    void write_to_file();
    std::string print_lines() const;
    std::string perform_command(std::string& input_stream);

    // static methods
    static void count_words(const std::string& line_to_count, int& word_count);
};


#endif //ASSIGNMENT1_TEXT_EDITOR_H
