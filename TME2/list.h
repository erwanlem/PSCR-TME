#pragma once

#include <cstddef>



template <typename T>
class List {
    class Node {
        public:
        T data;
        Node* next;
        Node(const T& data, Node& next = nullptr) : data(data), next(next) {};
    };

    public:
    // List head
    Node* head;

    List() : head(nullptr) {};
    T& operator[](size_t index) {
        Node* curr;
        for (curr = head; curr && index; curr = curr->next, index--) /*NOP*/;
        return curr->data;
    }
    ~List() {
        for (Node* curr = head; curr; ) {
            Node* tmp = curr->next;
            delete curr;
            curr = tmp;
        }
    }
    void push_front(const T& d) {
        head = new Node(d, head);
    }
};