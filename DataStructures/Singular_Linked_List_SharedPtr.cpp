#include <iostream>
#include <memory>

class Node {
public:
    int data;
    std::shared_ptr<Node> next;

    Node(int value) : data(value), next(nullptr) {}
};

// Define a LinkedList class to manage the list
class LinkedList {
private:
    std::shared_ptr<Node> head; // Pointer to the first node in the list

public:
    LinkedList() : head(nullptr) {}

    // Function to insert a new node at the beginning of the list
    void insertAtBeginning(int value) {
        std::shared_ptr<Node> newNode = std::make_shared<Node>(value);
        newNode->next = head;
        head = newNode;
    }

    // Function to display the elements of the list
    void display() {
        std::shared_ptr<Node> current = head;
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
            head = head->next;
            return;
        }

        std::shared_ptr<Node> current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                current->next = current->next->next;
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

    return 0;
}
