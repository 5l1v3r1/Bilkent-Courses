#include <iostream>
using namespace std;

#include "CircularLinkedList.h"

CircularLinkedList::CircularLinkedList() {
	tail = NULL;
}

CircularLinkedList::CircularLinkedList(const CircularLinkedList &input) {
	if (input.tail == NULL) {
		tail = NULL;
	}
	else {
		tail = new Node;
		tail -> data = input.tail -> data;
		Node *cur = input.tail -> next;
		Node *tmp = tail;
		while (cur != input.tail) {
			tmp -> next = new Node;
			tmp = tmp -> next;
			tmp -> data = cur -> data;
			cur = cur -> next;
		}
		tmp -> next = tail
	}
}

void CircularLinkedList::insert(int data) {
	if (tail == NULL) {
		tail = new Node;
		tail -> data = data;
		tail -> next = tail;
	}
	else {
		Node *tmp = new Node;
		tmp -> data = data;
		tmp -> next = tail -> next;
		tail -> next = tmp;
		tail = tmp;
	}
}

void CircularLinkedList::remove(int data) {
	if (tail -> data == data) {
		Node *cur = tail -> next;
		while (cur -> next != tail) {
			cur = cur -> next;
		}
		cur -> next = tail -> next;
		delete tail;
		tail = cur;
		return;
	}
	Node *cur = tail;
    do {
        if (cur -> next -> data == data) {
            Node *tmp = cur -> next;
            cur -> next = tmp -> next;
			delete tmp;
        }
		else
        	cur = cur -> next;
    } while(cur != tail -> next);
}

void CircularLinkedList::display() {
	if (tail != NULL) {
		Node *cur = tail -> next;
		do {
			cout << cur -> data << " ";
			cur = cur -> next;
		} while(cur != tail -> next);
		cout << endl;
	}
}
