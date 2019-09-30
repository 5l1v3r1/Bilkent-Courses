//
// Created by Boran Yildirim on 3.01.2017.
//

#include "Person.h"

Person::Person() {
    id = 0;
    name = "";
    phoneNumber = 0;
    prev = NULL;
    next = NULL;
}

Person::Person(const int &id, const string &name, const int &phoneNumber) :
        id(id), name(name),
        phoneNumber(phoneNumber){
    prev = NULL;
    next = NULL;
}

void Person::swap(Person &left, Person &right) {
    using std::swap;
    swap(left.id, right.id);
    swap(left.name, right.name);
    swap(left.phoneNumber, right.phoneNumber);

    swap(left.prev, right.prev);
    swap(left.next, right.next);
}

Person &Person::operator=(Person right) {
    swap(*this, right);
    return *this;
}

