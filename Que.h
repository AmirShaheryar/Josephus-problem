#pragma once
#include<iostream>
using namespace std;
class Queue
{
    struct Node
    {
        int data;
        Node* next;
        Node(int val) :data(val), next(nullptr)
        {}
    };
    Node* head;
    Node* tail;
public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
    }
    void Push(int val)
    {
        Node* temp = new Node(val);
        if (head == nullptr)
        {
            head = tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
            tail->next = nullptr;
        }
    }
    void Print()
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << "->";
            temp = temp->next;

        }
        cout << "nullptr";
        cout << "\n";
    }
    void pop()
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    int Size()
    {
        int s = 0;
        Node* temp = head;
        while (temp != nullptr)
        {
            s++;
            temp = temp->next;
        }
        return s;
    }
    int front()
    {
        Node* temp = head;
        return temp->data;
    }


};
