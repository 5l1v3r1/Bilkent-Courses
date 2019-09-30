//
// Created by Boran Yildirim on 3.01.2017.
//

#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H

#include <string>

using namespace std;

class Person {
public:
    Person();

    Person(const int &id, const string &name, const int &phoneNumber);

    Person& operator= (Person right);

private:
    void swap (Person& left, Person& right);
    // person properties
    int id;
    string name;
    int phoneNumber;

    Person *prev;
    Person *next;

    friend class PeopleDatabase;
};

#endif //HASH_CHAIN_H
