#include <iostream>
#include <stack>

//a stack is a data structure that follows the Last-In-First-Out (LIFO) principle,
// meaning that the last element added to the stack is the first one to be removed.
// It is often used for tasks that require maintaining a temporary history or keeping track of function calls, among other applications.
// C++ provides a way to implement a stack using several different approaches:


//Using the Standard Template Library (STL):
int main() {
    std::stack<int> myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    while (!myStack.empty()) {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }

    return 0;
}
//Using Arrays:
const int MAX_SIZE = 100;

class Stack {
private:
    int arr[MAX_SIZE];
    int top;

public:
    Stack() {
        top = -1; // Initialize the top of the stack
    }

    void push(int val) {
        if (top < MAX_SIZE - 1) {
            arr[++top] = val;
        } else {
            std::cout << "Stack overflow" << std::endl;
        }
    }

    void pop() {
        if (top >= 0) {
            --top;
        } else {
            std::cout << "Stack underflow" << std::endl;
        }
    }

    int peek() {
        if (top >= 0) {
            return arr[top];
        } else {
            std::cout << "Stack is empty" << std::endl;
            return -1; // Return a sentinel value for an empty stack
        }
    }

    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    Stack myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    while (!myStack.isEmpty()) {
        std::cout << myStack.peek() << " ";
        myStack.pop();
    }

    return 0;
}
//Using Linked Lists:
// Define a node structure for the linked list
struct Node {
    int data;
    Node* next;
};

class Stack {
private:
    Node* top; // Pointer to the top of the stack

public:
    Stack() {
        top = nullptr; // Initialize the top pointer to null for an empty stack
    }

    // Function to push an element onto the stack
    void push(int val) {
        Node* newNode = new Node;
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }

    // Function to pop an element from the stack
    void pop() {
        if (!isEmpty()) {
            Node* temp = top;
            top = top->next;
            delete temp; // Free memory of the old top node
        } else {
            std::cout << "Stack is empty. Cannot pop." << std::endl;
        }
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Function to get the top element of the stack without popping it
    int peek() {
        if (!isEmpty()) {
            return top->data;
        } else {
            std::cout << "Stack is empty. Cannot peek." << std::endl;
            return -1; // Return a sentinel value for an empty stack
        }
    }
};

int main() {
    Stack myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    std::cout << "Top element: " << myStack.peek() << std::endl;

    while (!myStack.isEmpty()) {
        std::cout << myStack.peek() << " ";
        myStack.pop();
    }

    return 0;
}
//The Stack class maintains a pointer called top that points to the top node of the linked list.
//The push method adds a new node to the top of the stack.
//The pop method removes the top node from the stack.
//The isEmpty method checks if the stack is empty.
//The peek method returns the value of the top element without removing it.
//The main function demonstrates the usage of the stack.
