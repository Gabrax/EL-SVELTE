#include <iostream>

//It consists of a sequence of nodes,
// where each node contains two parts: a data element and a reference (or pointer) to the next node in the sequence.

//In this example, we define a Node class to represent the individual elements in the list,
// and a LinkedList class to manage the list itself.
// The LinkedList class includes functions for inserting a node at the beginning of the list,
// displaying the list, and deleting a node by its value.

// Define a Node class to represent individual elements in the list
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Define a LinkedList class to manage the list
class LinkedList {
private:
    Node* head; // Pointer to the first node in the list

public:
    LinkedList() {
        head = nullptr;
    }

    // Function to insert a new node at the beginning of the list
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Function to display the elements of the list
    void display() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Function to delete a node by its value
    void deleteNode(int value) {
        if (head == nullptr)
            return; // List is empty

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }
};

int main()
{
    LinkedList myList;

    myList.insertAtBeginning(5);
    myList.insertAtBeginning(10);
    myList.insertAtBeginning(15);
    myList.insertAtBeginning(20);

    myList.display(); // Display the list: 20 -> 15 -> 10 -> 5 -> nullptr

    myList.deleteNode(10);

    myList.display(); // Display the list after deleting 10: 20 -> 15 -> 5 -> nullptr

    std::cin.get();
}