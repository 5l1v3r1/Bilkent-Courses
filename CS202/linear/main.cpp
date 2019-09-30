//
// Created by Boran Yildirim on 3.01.2017.
//

#include "PeopleDatabase.h"
#include <ctime>
#include <iostream>

using namespace std;

int main () {
    PeopleDatabase pd("/Users/boranyildirim/Desktop/CS202/Hash/people");
    clock_t begin = clock();
    pd.getPerson(745002384);
    clock_t end = clock();
    double time = double(end - begin) / (double)CLOCKS_PER_SEC;

    cout << time << endl;
    return 0;
}
