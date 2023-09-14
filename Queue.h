
#ifndef UNTITLED_QUEUE_H
#define UNTITLED_QUEUE_H

#include <bits/stdc++.h>

#define MAX 5

class Queue
{
private:
    int items[MAX], front, rear;
public:
    Queue()
    {
        front = -1;
        rear = -1;
    }

    bool isFull()
    {
        if (front == 0 && rear == MAX - 1)
        {
            return true;
        }
        return false;
    }

    bool isEmpty()
    {
        if (front == -1)
        {
            return true;
        }
        return false;
    }

    void enQueue(int element)
    {
        if(isFull())
        {
            std::cout << "Queue is full";
        }
        else
        {
            if(front == -1) front =0;
            rear++;
            items[rear] = element;
            std::cout << "Inserted" << element << std::endl;
        }
    }

    int deQueue() {
        int element;
        if (isEmpty()) {
            std::cout << "Queue is empty" << std::endl;
            return -1;
        } else
        {
            element = items[front];
            if (front >= rear)
            {
                front = -1;
                rear = -1;
            } /* Q has only one element, so we reset the queue after deleting it */
            else
            {
                front++;
            }
            std::cout << "deleted" << element << std::endl;
            return element;
        }
    }

    void display()
    {

        if(isEmpty())
        {
            std::cout << "empty Q" << std::endl;
        }
        else
        {
            std::cout << "Front index" << front << std::endl;
            std::cout << "Items ->" << front << std::endl;
            for(int i = front; i <= rear; i++)
            {
                std::cout << items[i] << std::endl;
                std::cout << "Rear index" << rear << std::endl;
            }

        }
    }

};



#endif //UNTITLED_QUEUE_H
