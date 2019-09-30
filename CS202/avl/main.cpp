#include <iostream>
#include "PeopleAVLTree.h"

using namespace std;

int main() {
    PeopleAVLTree p("/Users/boranyildirim/Desktop/CS202/Hash/people");
    clock_t begin, end;
    double time;
    int id;
    do {
        cout << "Enter id: ";
        cin >> id;
        begin = clock();
        p.search(id);
        end = clock();
        time = double(end - begin) / (double)CLOCKS_PER_SEC;
        cout << "Time: " << time << endl << endl;
    } while (id != -1);


    return 0;
}