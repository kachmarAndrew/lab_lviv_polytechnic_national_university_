#include <iostream>
#include <stdexcept>

template<typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;

        Node(const T& val) : value(val), next(nullptr) {}
    };

    Node* first;
    Node* last;
    int size_;

public:
    LinkedList() : first(nullptr), last(nullptr), size_(0) {}

    ~LinkedList() {
        clear();
    }

    // add to tail
    void add(const T& element) {
        Node* newNode = new Node(element);

        if (size_ == 0) {
            first = last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }
        size_++;
    }

    // add by index
    void add(int index, const T& element) {
        checkPositionIndex(index);

        Node* newNode = new Node(element);

        if (index == 0) {
            newNode->next = first;
            first = newNode;
            if (size_ == 0) {
                last = newNode;
            }
        }
        else if (index == size_) {
            last->next = newNode;
            last = newNode;
        }
        else {
            Node* prev = nodeAt(index - 1);
            newNode->next = prev->next;
            prev->next = newNode;
        }

        size_++;
    }

    void set(int index, const T& element) {
        Node* node = nodeAt(index);
        node->value = element;
    }

    T get(int index) const {
        return nodeAt(index)->value;
    }

    T getFirst() const {
        if (isEmpty())
            throw std::runtime_error("List is empty");
        return first->value;
    }

    T getLast() const {
        if (isEmpty())
            throw std::runtime_error("List is empty");
        return last->value;
    }

    T remove(int index) {
        checkElementIndex(index);

        Node* toDelete;
        T deletedValue;

        if (index == 0) {
            toDelete = first;
            deletedValue = toDelete->value;
            first = first->next;

            if (first == nullptr)
                last = nullptr;
        }
        else {
            Node* prev = nodeAt(index - 1);
            toDelete = prev->next;
            deletedValue = toDelete->value;
            prev->next = toDelete->next;

            if (index == size_ - 1)
                last = prev;
        }

        delete toDelete;
        size_--;
        return deletedValue;
    }

    bool contains(const T& element) const {
        Node* current = first;

        while (current != nullptr) {
            if (current->value == element)
                return true;
            current = current->next;
        }
        return false;
    }

    bool isEmpty() const {
        return size_ == 0;
    }

    int size() const {
        return size_;
    }

    void clear() {
        Node* current = first;

        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        first = last = nullptr;
        size_ = 0;
    }

    T removeFirst() {
        if (isEmpty())
            throw std::runtime_error("List is empty");

        Node* toDelete = first;
        T value = toDelete->value;

        first = first->next;

        if (first == nullptr)  // якщо список став пустим
            last = nullptr;

        delete toDelete;
        size_--;

        return value;
    }

    T removeLast() {
        if (isEmpty())
            throw std::runtime_error("List is empty");

        // якщо один елемент
        if (size_ == 1) {
            T value = first->value;
            delete first;
            first = last = nullptr;
            size_--;
            return value;
        }

        // шукаємо передостанній
        Node* current = first;
        while (current->next != last) {
            current = current->next;
        }

        T value = last->value;
        delete last;
        last = current;
        last->next = nullptr;

        size_--;
        return value;
    }

private:
    Node* nodeAt(int index) const {
        checkElementIndex(index);

        Node* current = first;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }

    void checkElementIndex(int index) const {
        if (index < 0 || index >= size_)
            throw std::out_of_range("Index out of bounds");
    }

    void checkPositionIndex(int index) const {
        if (index < 0 || index > size_)
            throw std::out_of_range("Index out of bounds");
    }
};