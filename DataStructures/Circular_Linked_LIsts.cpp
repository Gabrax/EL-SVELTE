#include <iostream>

//A circular linked list is a type of linked list in which the last node of the list points back to the first node, forming a loop.
// It's similar to a regular singly linked list, but the "next" pointer of the last node points to the first node instead of being NULL.
// Circular linked lists have various applications,
// such as implementing circular buffers or managing tasks in a round-robin scheduling algorithm.

//In this example, we first define a Node struct to represent the nodes of the circular linked list.
// Then, we define a CircularLinkedList class with methods to insert elements at the end and display the contents of the list.
// The insert method handles both the case when the list is empty and when it's not.
// The display method traverses the circular list and prints its elements.


// Define a structure for a node in the circular linked list
    struct Node {
        int data;
        Node* next;

        Node(int value) : data(value), next(nullptr) {}
    };

// Define a class for the circular linked list
    class CircularLinkedList {
    private:
        Node* head; // Pointer to the head of the list
    public:
        CircularLinkedList() : head(nullptr) {}

        // Function to insert a new node at the end of the list
        void insert(int data) {
            Node* newNode = new Node(data);
            if (!head) {
                // If the list is empty, make the new node the head and point it to itself
                head = newNode;
                head->next = head;
            } else {
                // Find the last node and update its "next" pointer to the new node
                Node* temp = head;
                while (temp->next != head) {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->next = head;
            }
        }

        // Function to display the elements of the circular linked list
        void display() {
            if (!head) {
                std::cout << "List is empty." << std::endl;
                return;
            }
            Node* temp = head;
            do {
                std::cout << temp->data << " ";
                temp = temp->next;
            } while (temp != head);
            std::cout << std::endl;
        }
    };

    int main() {
        CircularLinkedList myList;

        // Insert some elements into the circular linked list
        myList.insert(1);
        myList.insert(2);
        myList.insert(3);
        myList.insert(4);

        // Display the elements
        myList.display(); // Output: 1 2 3 4

        std::cin.get();
}
