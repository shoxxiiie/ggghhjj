#include <iostream>
#include <stdexcept>

namespace CustomExceptions {
    class ListException : public std::exception {
    public:
        virtual const char* what() const noexcept override {
            return " ";
        }
    };

    class MemoryAllocationException : public ListException {
    public:
        const char* what() const noexcept override {
            return " ";
        }
    };

    class EmptyListException : public ListException {
    public:
        const char* what() const noexcept override {
            return " ";
        }
    };
}

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_front(int value) {
        Node* newNode = new (std::nothrow) Node(value);
        if (!newNode) throw CustomExceptions::MemoryAllocationException();
        
        newNode->next = head;
        if (head) head->prev = newNode;
        else tail = newNode;
        head = newNode;
    }

    void push_back(int value) {
        Node* newNode = new (std::nothrow) Node(value);
        if (!newNode) throw CustomExceptions::MemoryAllocationException();
        
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        else head = newNode;
        tail = newNode;
    }

    void pop_front() {
        if (!head) throw CustomExceptions::EmptyListException();
        
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) throw CustomExceptions::EmptyListException();
        
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }
};

int main() {
    try {
        DoublyLinkedList list;
        list.pop_front(); 
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << std::endl;
    }
    return 0;
}
