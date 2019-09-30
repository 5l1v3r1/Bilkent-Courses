//
// Created by Boran Yildirim on 3.01.2017.
//

#include <fstream>
#include <iostream>
#include "PeopleDatabase.h"

PeopleDatabase::PeopleDatabase(const string &file) {
    for (int i = 0; i < SIZE; ++i) {
        database[i] = NULL;
    }

    readFile(file);
}

PeopleDatabase::~PeopleDatabase() {

}

void PeopleDatabase::addPerson(int id, string name, int phone) {
    int index = hash(id);
    if (database[index] == NULL) {
        database[index] = new Person(id, name, phone);
    }
    else {
        Person *p = new Person(id, name, phone);
        p->next = database[index];
        //database[index]->prev = p;
        database[index] = p;
    }
}

void PeopleDatabase::deletePerson(int id) {

}

void PeopleDatabase::getPerson(int id) {
    int index = hash(id);
    Person *cur = database[index];
    int attempt = 0;
    while (cur != NULL) {
        attempt++;
        if (cur->id == id) {
            cout << "Found in " << attempt << " attempts." << endl;
            cout << "id: " << cur->id << " name: " << cur->name << " phone: " << cur->phoneNumber << endl;
            break;
        }
        cur = cur->next;
    }
}

int PeopleDatabase::hash(int id) {
    return id % SIZE;   // simple hash function
}

void PeopleDatabase::readFile(const string &file) {

    ifstream myfile (file.c_str());
    if ( myfile.is_open() ) {

        int id = 0, phone = 0;
        string name;
        while ( myfile >> id >> name >> phone ) {
            addPerson(id, name, phone);
        }
    }
    else {  // the file is empty
        cout << "File is empty." << endl;
    }
}
