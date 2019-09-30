#include "LinkedList.h"

#include <iostream>
using namespace std;

LinkedList::LinkedList() {
    head = NULL;
}

LinkedList::LinkedList(const LinkedList &input) {
    if (input.head == NULL) {
        head = NULL;
    }
    else {
        head = new Node;
        head -> data = input.head -> data;
        Node *cur = input.head -> next;
        Node *tail = head;
        while (cur != NULL) {
            tail -> next = new Node;
            tail = tail -> next;
            tail -> data = cur -> data;
            cur = cur -> next;
        }
        tail -> next = NULL;
    }
}

void LinkedList::insert(int data) {
    if (head == NULL) {
        head = new Node;
        head -> data = data;
        head -> next = NULL;
    }
    else {
        Node *tmp = new Node;
        tmp -> data = data;
        tmp -> next = head;
        head = tmp;
    }
}

void LinkedList::remove(int data) {
    if (head -> data == data) {
        Node *tmp = head;
        head = head -> next;
        delete tmp;
        return;
    }
    Node *cur = head;
    while (cur -> next != NULL) {
        if (cur -> next -> data == data) {
            Node *tmp = cur -> next;
            cur -> next = tmp -> next;
            delete tmp;
        }
        else
            cur = cur -> next;
    }
}

void LinkedList::display() {
    Node *cur = head;
    while (cur != NULL) {
        cout << cur -> data << " ";
        cur = cur -> next;
    }
    cout << endl;
}

void LinkedList::reverse() {
    Node *prev = NULL;
    Node *cur = head;
    Node *next;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
}
