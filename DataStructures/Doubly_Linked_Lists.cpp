#include <iostream>

//This bidirectional linkage allows for efficient traversal
// in both directions (forward and backward) compared to a singly linked list.

//in this code, we define a Node struct that has data, next, and prev pointers.
// The DoublyLinkedList class has methods for appending, prepending, deleting nodes,
// and displaying the list in both forward and backward directions.
// The main function demonstrates how to use the doubly linked list.

//Remember to handle memory deallocation properly when deleting nodes to avoid memory leaks in a real-world application.

// Define a Node structure
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// Define a DoublyLinkedList class
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Function to insert a new node at the end of the list
    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Function to insert a new node at the beginning of the list
    void prepend(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Function to delete a node with a given value
    void deleteNode(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current == head) {
                    head = current->next;
                    if (head)
                        head->prev = nullptr;
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                return;
            }
            current = current->next;
        }
    }

    // Function to display the list from the head to tail
    void displayForward() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Function to display the list from the tail to head
    void displayBackward() {
        Node* current = tail;
        while (current) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }
};

int main()
{
    DoublyLinkedList dll;
    dll.append(1);
    dll.append(2);
    dll.append(3);
    dll.prepend(0);

    dll.displayForward();  // Output: 0 1 2 3
    dll.displayBackward(); // Output: 3 2 1 0

    dll.deleteNode(2);
    dll.displayForward();  // Output: 0 1 3

    std::cin.get();
}
