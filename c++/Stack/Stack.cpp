#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

Stack::Stack(){
    top = NULL;
}

Stack::Stack(const Stack &input){
    if (input.top == NULL)
        top = NULL;
    else {
        top = new Node;
        top -> data = input.top -> data;
        Node *cur = input.top -> next;
        Node *tail = top;
        while (cur != NULL) {
            tail -> next = new Node;
            tail = tail -> next;
            tail -> data = cur -> data;
            cur = cur -> next;
        }
        tail -> next = NULL;
    }
}

void Stack::push(string data) {
    Node *tmp = new Node;
    tmp -> data = data;
    tmp -> next = NULL;
    if (top == NULL) {
        top = tmp;
    }
    else {
        tmp -> next = top;
        top = tmp;
    }
}

string Stack::pop() {
    if (top == NULL) {
        return NULL;
    }
    else {
        Node *temp = top;
        string tmpInt = top -> data;
        top = top -> next;
        delete temp;
        return tmpInt;
    }
}

bool Stack::isEmpty() {
    return top == NULL;
}

void Stack::display() {
    Node *cur = top;
    while (cur != NULL){
        cout << cur -> data << " ";
        cur = cur -> next;
    }
    cout << endl;
}

string Stack::getTop() {
    return top -> data;
}
