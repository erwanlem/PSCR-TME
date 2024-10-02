#pragma once

#include <cstddef>


template <typename T>
class List {

    class Node {
        public:
        T data;
        Node* next;
        Node(const T data, Node* next = nullptr) : data(data), next(next) {};

        Node* operator++() {
            return next;
        }

        Node* operator*() {
            return data;
        }
    };

    public:
    class iterator {
        Node* node;

        public:
            iterator(Node* node) : node(node) {}

            bool operator==(const iterator& o) const {
                return node == o.node;
            }

            bool operator!=(const iterator& o) const {
                return !((*this) == o);
            }

            iterator operator++(int) {
                iterator ret(*this->node);
                node = node->next;
                return ret;
            }

            iterator operator++() {
                node = node->next;
                return node;
            }

            T& operator*() const {
                return node->data;
            }

    };

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

    void push_front(const T d) {
        head = new Node(d, head);
    }

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

};

