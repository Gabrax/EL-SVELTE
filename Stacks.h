#ifndef UNTITLED_STACKS_H
#define UNTITLED_STACKS_H

#include <bits/stdc++.h>

#define MAX 1000

class Stack
{
private:
    int top;
public:
    int a[MAX];

    Stack()
    {
        top = -1;
    }
    bool push(int x);
    int pop();
    int peek();
    bool isEmpty();
};

bool Stack::push (int x)
{
    if (top >= (MAX - 1))
    {
        std::cout << "Stack oferlow";
        return false;
    }
    else
    {
        a[++top] = x;
        std::cout << x << " pushed into stack\n";
        return true;
    }
}

int Stack::pop()
{
    if (top < 0)
    {
        std::cout << "Stack underflow";
        return 0;
    }
    else
    {
        int x = a[top--];
        return x;
    }
}

#endif //UNTITLED_STACKS_H
