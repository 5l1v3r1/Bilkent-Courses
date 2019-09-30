#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue() {
    first = NULL;
    last = NULL;
}

Queue::Queue(Queue &input) {
    if (input.isEmpty()) {
        first = NULL;
        last = NULL;
    }
    else {
        first = new Node;
        first -> data = input.first -> data;
        last = first;
        Node *cur = input.first -> next;
        Node *tail = last;
        while (cur != NULL) {
            tail -> next = new Node;
            tail = tail -> next;
            tail -> data = cur -> data;
            cur = cur -> next;
        }
        tail -> next = NULL;
    }
}

void Queue::dequeue() {
    if (!isEmpty()) {
        if (first == last) {
            delete first;
            first = NULL;
        }
        else {
            Node *tmp = first;
            first = first -> next;
            delete tmp;
        }
    }
}

void Queue::enqueue(int data) {
    if (isEmpty()) {
        Node *x = new Node;
        x -> data = data;
        x -> next = NULL;
        first = x;
        last = x;
    }
    else {
        last -> next = new Node;
        last -> next -> data = data;
        last -> next -> next = NULL;
        last = last -> next;
    }
}

bool Queue::isEmpty() {
    return first == NULL;
}

void Queue::display() {
    Node *cur = first;
    while (cur != NULL) {
        cout << cur -> data << " ";
        cur = cur -> next;
    }
    cout << endl;
}
