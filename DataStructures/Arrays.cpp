/*#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include "hehe.h"
#include "Rekurencja.h"
#include "Stacks.h"
#include "Queue.h"
#include "LinkedLists.h"

#define LOG(x) std::cout << x << '\n';

int main() {
    Write("siema");
    LOG("hello");
    int a = 5;
    int b = 6;
    int sum;
    if(a < b)
    {
        sum = a + b;
    }
    std::cout << sum << std::endl;


    int var = 8;
    void* ptr = &var;

    int liczba = 123;
    printf( "%i\n", sizeof(liczba) ); //pokazuje rozmiar którą zajmuje w pamięci




    Entity entity;
    entity.SetLevel(entity.EntityLevelWarning);
    entity.Error("error");
    entity.Warn("warning");
    entity.Info("info");

    int sumOfnumbers = recursiveSum(3);
    int sumofevenSquares = evenSquares(5);
    int sumofevenSquares2 = evenSquares2(2);
    int nthFibnumber = fibNumber(9);
    std::string hello = "hello";
    char substring = 'e';
    bool containsstring = linear(hello, substring, hello.length()-1);

    std::cout << "sum: " << sumOfnumbers << std::endl;

class Stack d;
d.push(2);
d.push(3);
d.push(5);
int elementsPoped = d.pop();

std::cout << elementsPoped << std::endl;

class Queue q;
q.deQueue();
q.enQueue(1);
q.enQueue(2);
q.enQueue(3);
q.enQueue(4);
q.enQueue(5);

q.deQueue();
q.display();

// linked list
Node* head;
Node* one = NULL;
Node* two = NULL;
Node* three = NULL;

// allocate 3 nodes in the heap
one = new Node();
two = new Node();
three = new Node();

// assign value values
one -> value =1;
two -> value =2;
three -> value =3;

// assign value values
one -> next =two;
two -> next =three;
three -> next =NULL;

// print the linked list value
head = one;
while(head != NULL)
{
    std::cout << "head value" << head->value << std::endl;
    head = head ->next;
}

    std::cin.get();
}
