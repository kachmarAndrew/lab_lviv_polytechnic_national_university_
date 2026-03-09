#include <iostream>
#include <stack>

using namespace std;

// Функція для вставки елемента в низ стеку
void insertAtBottom(stack<int>& st, int value) {
    if (st.empty()) {
        st.push(value);
        return;
    }

    int topElement = st.top();
    st.pop();

    insertAtBottom(st, value);

    st.push(topElement);
}

// Функція для перевертання стеку
void reverseStack(stack<int>& st) {
    if (st.empty())
        return;

    int topElement = st.top();
    st.pop();

    reverseStack(st);

    insertAtBottom(st, topElement);
}

int main() {
    stack<int> st;

    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);

    reverseStack(st);

    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }

    return 0;
}