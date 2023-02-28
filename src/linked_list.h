//
// Created by Jack MacKinnon on 2023-01-18.
//

#ifndef ASSIGNMENT1_LINKED_LIST_H
#define ASSIGNMENT1_LINKED_LIST_H
#include <iostream>

class LinkedList {
private:
    struct Node {
        std::string m_data {"-1"};
        Node *m_next {nullptr};
    };
    Node* m_start {nullptr};
    int m_node_count {0};
public:
    // Constructors and Destructors
    LinkedList();
    virtual ~LinkedList();

    // Class Methods
    void add(std::string text);
    void insert_before(std::string text, int position);
    void remove(int index);
    void push_back(std::string text);
    int get_node_count() const;

    // Friend functions and overloaded operators
    friend std::ostream& operator<<(std::ostream& output, LinkedList& list);
    std::string operator[](int index) const;

};

#endif //ASSIGNMENT1_LINKED_LIST_H
