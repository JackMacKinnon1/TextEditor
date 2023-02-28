//
// Created by Jack MacKinnon on 2023-01-18.
//

#include "linked_list.h"
#include <utility>

//Constructors and Destructors
LinkedList::LinkedList() :m_start(nullptr) {}
LinkedList::~LinkedList() {
    auto node = m_start;
    while (node != nullptr) {
        auto temp = node;
        node = node->m_next;
        delete temp;
    }
}

// Class methods
void LinkedList::add(std::string text) {
    // create a new node
    auto new_node = new Node();
    new_node->m_data = std::move(text);

    if (m_start == nullptr) {
        // attach it to the start of the linked list
        m_start = new_node;
    } else {
        // attach it to the end of the existing chain
        auto node = m_start;
        Node* prev = nullptr;

        // find the last node
        while (node != nullptr) {
            prev = node;
            node = node->m_next;
        }

        // attach new node to the node at the end of the chain
        prev->m_next = new_node;
    }

    m_node_count++;
}

void LinkedList::insert_before(std::string text, int position) {

    // check if index provided is valid
    if (position < 0 || position > m_node_count) {
        return;
    }

    // create a new node
    auto new_node = new Node();
    new_node->m_data = std::move(text);

    // locate node to insert before
    auto node = m_start;
    Node* prev = nullptr;

    int curr_pos = 0;
    while (node != nullptr) {
        if (curr_pos++ == position) {
            break;
        }
        prev = node;
        node = node->m_next;
    }

    // is this the first node?
    if (prev == nullptr) {
        // first node
        new_node->m_next = m_start;
        m_start = new_node;
    } else {
        // other node
        new_node->m_next = prev->m_next;
        prev->m_next = new_node;
    }

    m_node_count++;
}

void LinkedList::remove(int index) {
    // check if index provided is valid
    if (index < 0 || (index > m_node_count - 1)) {
        return;
    }
    auto node = m_start;
    Node* prev = nullptr;
    // determine if we are deleting the first node
    if (index == 0) {
        m_start = node->m_next;
    } else {
        int curr_pos = 0;
        while (curr_pos < index) {
            prev = node;
            node = node->m_next;
            curr_pos++;
        }

        //detach node from chain
        prev->m_next = node->m_next;
    }

    delete node;

    m_node_count--;
}

void LinkedList::push_back(std::string text) {
    // creating new node
    auto new_node = new Node();
    new_node->m_data = std::move(text);

    // attaching node to the front of the linked list
    new_node->m_next = m_start;
    m_start = new_node;
    m_node_count++;
}

int LinkedList::get_node_count() const {return m_node_count;}

// Friend functions and overloaded operators
std::ostream& operator<<(std::ostream& output, LinkedList& list) {
    auto node = list.m_start;
    while (node != nullptr) {
        output << node->m_data;
        if (node->m_next != nullptr) {
            output << "\n";
        }
        node = node->m_next;
    }
    return output;
}

std::string LinkedList::operator[](int index) const {
    // validate the index provided
    if (index < 0 || index > m_node_count) {
        return "";
    }

    auto node = m_start;
    int iterations = 0;
    //finding the data at that index
    while (iterations++ < index) {
        node = node->m_next;
    }

    return node->m_data;
}