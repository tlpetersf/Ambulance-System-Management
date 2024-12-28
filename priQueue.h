#pragma once
#include <iostream>
using namespace std;
template <typename T>
class priNode
{
private:
    T item;         // A data item
    int pri;        // Priority of the item
    priNode<T>* next; // Pointer to the next node

public:
    priNode(const T& r_Item, int PRI)
    {
        setItem(r_Item, PRI);
        next = nullptr;
    }
    void setItem(const T& r_Item, int PRI)
    {
        item = r_Item;
        pri = PRI;
    }
    void setNext(priNode<T>* nextNodePtr)
    {
        next = nextNodePtr;
    }

    T getItem(int& PRI) const
    {
        PRI = pri;
        return item;
    }

    priNode<T>* getNext() const
    {
        return next;
    }

    int getPri() const
    {
        return pri;
    }
}; // end Node

// This class implements the priority queue as a sorted list (Linked List)
// The item with the highest priority is at the front of the queue
template <typename T>
class priQueue
{
    priNode<T>* head;
    int count;

public:
    priQueue() : head(nullptr) { count = 0; }

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {

            newNode->setNext(head);
            head = newNode;
            count++;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        count++;
    }
    void enqueuefront(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        if (isEmpty()) {
            head = newNode;
            return;
        }
        else {
            newNode->setNext(head);
            head = newNode;
            return;
        }
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        count--;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;
        pri = head->getPri();
        topEntry = head->getItem(pri);

        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void print() {
        if (isEmpty()) {
            std::cout << "Queue is empty." << std::endl;
            return;
        }


        priNode<T>* current = head;
        while (current != nullptr) {
            int pri;
            T item = current->getItem(pri);
            cout << *item;
            if (current->getNext() != nullptr)
                cout << ", ";
            current = current->getNext();
        }
        cout << std::endl;
    }
    int getCount() { return count; }

};