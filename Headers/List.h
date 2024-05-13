#pragma once
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node {
public:

    T val;
    Node* next;
    Node(T val1) {
        this->val = val1;
        this->next = nullptr;
    }
};

template <typename T>
class MyList {
    Node<T>* head;
public:
    MyList()
    {
        head = nullptr;
    }
    MyList(T val1)
    {
        head = new Node<T>(val1);
    }
    Node<T>* begin() { return head; }
    Node<T>* end() { return nullptr; }
    bool isEmpty()
    {
        return head == nullptr;
    }
    void Push(T val)
    {
        Node<T>* tmp = new Node<T>(val);
        tmp->next = head;
        head = tmp;
    }
    void PushBack(T val)
    {
        Node<T>* tmp = new Node<T>(val);
        if (isEmpty())
        {
            head = tmp;
        }
        else {
            Node<T>* curr = head;
            while (curr->next != nullptr)
            {
                curr = curr->next;
            }
            curr->next = tmp;
        }
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "List is Empty\n";
            return;
        }
        Node<T>* curr = head;
        while (curr)
        {
            cout << curr->val << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    void search()
    {
        if (isEmpty())
        {
            cout << "List is empty\n";
            return;
        }
        Node<T>* curr = head;
        while (curr&&curr->val)
        {
            cout << curr->val << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    T pop()
    {
        if (isEmpty())
        {
            cout << "List is empty\n";
            return T();
        }
        Node<T>* tmp = head;
        T val = tmp->val;
        head = head->next;
        delete tmp;
        return val;
    }
    T PopBack()
    {
        if (isEmpty())
        {
            cout << "List is empty\n";
            return T(); // Return default value for type T
        }
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            return T(); // Return default value for type T
        }
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr->next != nullptr)
        {
            prev = curr;
            curr = curr->next;
        }
        prev->next = nullptr;
        T val = curr->val;
        delete curr;
        return val;
    }
    void makeNull()
    {
        Node<T>* curr = head;
        while (curr != nullptr)
        {
            Node<T>* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
    }
    void reverseList()
    {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        while (curr != nullptr)
        {
            Node<T>* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        head = prev;
    }
    ~MyList()
    {
        Node<T>* curr = head;
        while (curr != nullptr)
        {
            Node<T>* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
    }
};

