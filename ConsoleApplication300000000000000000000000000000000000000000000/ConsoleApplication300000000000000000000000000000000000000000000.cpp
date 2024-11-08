#include <iostream>
#include <initializer_list>
#include <stdexcept>

class List {
private:
    struct Node {
        int value;
        Node* prev;
        Node* next;
        Node(int v) : value(v), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size; 

public:
    
    List() : head(nullptr), tail(nullptr), size(0) {}

    List(std::initializer_list<int> values) : head(nullptr), tail(nullptr), size(0) {
        for (int value : values) {
            Append(value);
        }
    }

    ~List() {
        Clear();
    }

    void Append(int value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else {
            head = tail = newNode;
        }
        size++;
    }

    size_t GetSize() const {
        return size;
    }

    int& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    void DeleteByValue(int value) {
        Node* current = head;
        while (current) {
            if (current->value == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }
                delete current;
                size--;
                return;
            }
            current = current->next;
        }
    }

    void RemoveDuplicates() {
        Node* current = head;
        while (current) {
            Node* runner = current->next;
            while (runner) {
                if (runner->value == current->value) {
                    Node* toDelete = runner;
                    if (runner->prev) {
                        runner->prev->next = runner->next;
                    }
                    if (runner->next) {
                        runner->next->prev = runner->prev;
                    }
                    if (runner == tail) {
                        tail = runner->prev;
                    }
                    runner = runner->next;
                    delete toDelete;
                    size--;
                }
                else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    int FindMax() const {
        if (!head) throw std::runtime_error("List is empty");
        int maxVal = head->value;
        Node* current = head->next;
        while (current) {
            if (current->value > maxVal) {
                maxVal = current->value;
            }
            current = current->next;
        }
        return maxVal;
    }

    int FindMin() const {
        if (!head) throw std::runtime_error("List is empty");
        int minVal = head->value;
        Node* current = head->next;
        while (current) {
            if (current->value < minVal) {
                minVal = current->value;
            }
            current = current->next;
        }
        return minVal;
    }

    void PrintReverse() const {
        Node* current = tail;
        while (current) {
            std::cout << current->value << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }

    void Clear() {
        Node* current = head;
        while (current) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
        size = 0;
    }

    void Print() const {
        Node* current = head;
        while (current) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};
