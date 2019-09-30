//
// Created by Boran Yildirim on 3.01.2017.
//

#include <iostream>
#include <fstream>
#include "PeopleAVLTree.h"

using namespace std;

PeopleAVLTree::PeopleAVLTree(string file) {
    root = new Person;
    NIL = new Person;
    root = NIL;
    NIL->height = 0;
    NIL->left = NIL->right = NULL;

    readFile(file);
}


PeopleAVLTree::~PeopleAVLTree() {
    dealloc(root);
}

void PeopleAVLTree::dealloc(Person *person) {
    if (person != NIL) {
        dealloc(person->left);
        dealloc(person->right);
        delete person;
        person = NIL;
    }
}


bool PeopleAVLTree::isEmpty() {
    return root == NIL;
}


void PeopleAVLTree::search(int id) {
    search(root, id);
}

void PeopleAVLTree::search(Person *person, int id) {
    if (isEmpty() || person == NULL)
        return;
    if (person->id == id)
        cout << "id: " << person->id << " name: " << person->name << " phone: " << person->phoneNumber << endl;
    if (id < person->id)
        search(person->left, id);
    else if (id > person->id)
        search(person->right, id);
}


void PeopleAVLTree::insert(Person *&person) {
    root = insert(root, person);
}

Person *PeopleAVLTree::insert(Person *node, Person *person) {
    if (person != NULL) {
        if (node == NIL) {
            node = person;
            node->left = NIL;
            node->right = NIL;
            node->height = 1;

            return node;
        }

        if (person->id <= node->id)
            node->left = insert(node->left, person);
        else if (person->id > node->id)
            node->right = insert(node->right, person);
    }
    return balance(node);
}


void PeopleAVLTree::remove(int id) {

}

int PeopleAVLTree::max(int a, int b) {
    return a >b ? a : b;
}

void PeopleAVLTree::setHeight(Person *person) {
    person->height = 1 + max(person->left->height, person->right->height);
}

Person *PeopleAVLTree::rotateLeft(Person *person) {
    Person *tmp = person->left;
    person->left = tmp->right;
    tmp->right = person;
    setHeight(person);
    setHeight(tmp);

    return tmp;
}

Person *PeopleAVLTree::rotateRight(Person *person) {
    Person *tmp = person->right;
    person->right = tmp->left;
    tmp->left = person;
    setHeight(person);
    setHeight(tmp);

    return tmp;
}

Person *PeopleAVLTree::balance(Person *person) {
    setHeight(person);

    if (person->left->height > person->right->height + 1) {
        if (person->left->right->height > person->left->left->height)
            person->left = rotateRight(person->left);
        person = rotateLeft(person);
    }
    else if (person->right->height > person->left->height + 1) {
        if (person->right->left->height > person->right->right->height)
            person->right = rotateLeft(person->right);
        person = rotateRight(person);
    }

    return person;
}

void PeopleAVLTree::readFile(const string &file) {
    ifstream myfile (file.c_str());
    if ( myfile.is_open() ) {

        int id = 0, phone = 0;
        string name;
        while ( myfile >> id >> name >> phone ) {
            Person *p = new Person;
            p->id = id;
            p->name = name;
            p->phoneNumber = phone;
            insert(p);
        }
    }
    else {  // the file is empty
        cout << "File is empty." << endl;
    }

}

