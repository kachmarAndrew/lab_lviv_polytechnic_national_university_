#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////
// ШАБЛОН ЧЕРГИ
/////////////////////////////////////////////////////

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* front;
    Node* rear;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    // Додавання елемента
    void enqueue(T value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Видалення елемента
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty! Cannot remove.\n";
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
    }

    // Перегляд першого елемента
    T peek() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        return front->data;
    }

    // Вивід усіх елементів
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        Node* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Звільнення пам’яті
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    ~Queue() {
        clear();
    }
};

/////////////////////////////////////////////////////
// ПРИКЛАД СТРУКТУРИ
/////////////////////////////////////////////////////

struct Student {
    string surname;
    float average;
};

// Перевантаження оператора для виводу
ostream& operator<<(ostream& os, const Student& s) {
    os << s.surname << " (" << s.average << ")";
    return os;
}

/////////////////////////////////////////////////////
// ГОЛОВНА ПРОГРАМА
/////////////////////////////////////////////////////

int main() {

    cout << "QUEUE OF INTS:\n";
    Queue<int> intQueue;
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);
    intQueue.display();

    cout << "After dequeue:\n";
    intQueue.dequeue();
    intQueue.display();


    cout << "\nQUEUE OF DOUBLES:\n";
    Queue<double> doubleQueue;
    doubleQueue.enqueue(3.14);
    doubleQueue.enqueue(2.71);
    doubleQueue.display();


    cout << "\nQUEUE OF STUDENTS:\n";
    Queue<Student> studentQueue;

    Student s1 = {"Ivanenko", 89.5};
    Student s2 = {"Petrenko", 92.3};

    studentQueue.enqueue(s1);
    studentQueue.enqueue(s2);

    studentQueue.display();

    return 0;
}
