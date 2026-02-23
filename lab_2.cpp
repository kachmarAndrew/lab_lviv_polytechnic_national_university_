#include <iostream>
#include <cstring>

using namespace std;

//////////////////////////////////////////////////////////
// ЧАСТИНА 1. Перетин двох масивів через стек
//////////////////////////////////////////////////////////

struct IntNode {
    int data;
    IntNode* next;
};

class IntStack {
private:
    IntNode* top;

public:
    IntStack() {
        top = nullptr;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int value) {
        IntNode* newNode = new IntNode;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!\n";
            return -1;
        }
        IntNode* temp = top;
        int value = temp->data;
        top = temp->next;
        delete temp;
        return value;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

bool existsInArray(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value)
            return true;
    }
    return false;
}

void intersectionUsingStack(int arr1[], int size1, int arr2[], int size2) {
    IntStack stack;

    // Додаємо в стек всі елементи першого масиву
    for (int i = 0; i < size1; i++) {
        stack.push(arr1[i]);
    }

    cout << "Intersection: ";

    while (!stack.isEmpty()) {
        int value = stack.pop();
        if (existsInArray(arr2, size2, value)) {
            cout << value << " ";
        }
    }

    cout << endl;
}

//////////////////////////////////////////////////////////
// ЧАСТИНА 2. Стек студентів
//////////////////////////////////////////////////////////

struct Student {
    char surname[50];
    float average;
};

struct StudentNode {
    Student data;
    StudentNode* next;
};

class StudentStack {
private:
    StudentNode* top;

public:
    StudentStack() {
        top = nullptr;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(Student s) {
        StudentNode* newNode = new StudentNode;
        newNode->data = s;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot remove.\n";
            return;
        }

        StudentNode* temp = top;
        top = temp->next;
        delete temp;

        cout << "Student removed from stack.\n";
    }

    void peek() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }

        cout << "Top student: "
             << top->data.surname
             << ", Average: "
             << top->data.average << endl;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }

        StudentNode* current = top;

        cout << "\nStudents in stack:\n";
        while (current != nullptr) {
            cout << "Surname: "
                 << current->data.surname
                 << ", Average: "
                 << current->data.average << endl;
            current = current->next;
        }
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    ~StudentStack() {
        clear();
    }
};

//////////////////////////////////////////////////////////
// ГОЛОВНА ПРОГРАМА
//////////////////////////////////////////////////////////

int main() {

    ////////////////////////////////
    // Перетин масивів
    ////////////////////////////////

    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {3, 4, 7, 8};

    intersectionUsingStack(arr1, 5, arr2, 4);

    ////////////////////////////////
    // Робота зі стеком студентів
    ////////////////////////////////

    StudentStack stack;
    int choice;

    do {
        cout << "\n1. Add student\n";
        cout << "2. Remove student\n";
        cout << "3. View top student\n";
        cout << "4. Display all\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student s;
                cout << "Enter surname: ";
                cin >> s.surname;
                cout << "Enter average mark: ";
                cin >> s.average;
                stack.push(s);
                break;
            }
            case 2:
                stack.pop();
                break;
            case 3:
                stack.peek();
                break;
            case 4:
                stack.display();
                break;
            case 0:
                stack.clear();
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
