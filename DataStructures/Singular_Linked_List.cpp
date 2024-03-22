#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <stack>
#include <queue>
#include <cctype>
#include <memory>

/*struct Node{
    int value;
    Node* next;
};*/

struct Node {
    int value;
    std::unique_ptr<Node> next; // Using unique_ptr for ownership management
};

struct Node2 {
    int value;
    std::shared_ptr<Node2> next; // Using shared_ptr for shared ownership
};



int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    /*Node* head;
    Node* one;
    Node* two;
    Node* three;

    one = new Node();
    two = new Node();
    three = new Node();

    

    one->value = 1;
    two->value = 2;
    three->value = 3;

    one->next = two;
    two->next = three;
    three->next = NULL;

    head = one;
    while(head!=NULL){
        std::cout << head->value;
        head = head->next;
    }*/

    /*std::unique_ptr<Node> head = std::make_unique<Node>();
    std::unique_ptr<Node> one = std::make_unique<Node>();
    std::unique_ptr<Node> two = std::make_unique<Node>();
    std::unique_ptr<Node> three = std::make_unique<Node>();

    // Assigning values
    head->value = 0; // Dummy value for head
    one->value = 1;
    two->value = 2;
    three->value = 3;

    // Linking nodes
    head->next = std::move(one);
    head->next->next = std::move(two);
    head->next->next->next = std::move(three);

    // Traversing and printing the linked list
    Node* current = head.get(); // get raw pointer
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next.get(); // get raw pointer from the unique_ptr
    }*/
    
    std::shared_ptr<Node2> head = std::make_shared<Node2>();
    std::shared_ptr<Node2> one = std::make_shared<Node2>();
    std::shared_ptr<Node2> two = std::make_shared<Node2>();
    std::shared_ptr<Node2> three = std::make_shared<Node2>();

    // Assigning values
    head->value = 0; // Dummy value for head
    one->value = 1;
    two->value = 2;
    three->value = 3;

    // Linking nodes
    head->next = one;
    one->next = two;
    two->next = three;

    // Traversing and printing the linked list
    std::shared_ptr<Node2> current = head; // Copy head, shared ownership
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next; // Automatic shared ownership, no need for get()
    }


    return 0;
}
