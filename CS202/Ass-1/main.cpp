#include "sorting.h"
#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    /* code */
    const int size = static_cast<const int>(pow(2, 20));
    int arr[size];
    int arr2[size];
    //int arr3[size];
    clock_t begin, end;
    double time;

    begin = clock();
    for (int i = 0; i < size; i++){
        arr[i] = size - i;
        arr2[i] = arr[i];
        //arr3[i] = arr[i];
    }
    end = clock();
    time = double(end - begin) / (double)CLOCKS_PER_SEC;
    cout << "***** The time for constructing the arrays: " << time << endl;


    cout << "***** Insertion Sort *****" << endl;
    //display(arr, size);
    begin = clock();
    InsertionSort(arr, size);
    end = clock();
    time = double(end - begin) / (double)CLOCKS_PER_SEC;
    cout << "Insertion Sort time: " << time << endl;
    //display(arr, size);
    cout << "***** End Insertion Sort *****" << endl;


    cout << "***** Merge Sort *****" << endl;
    //display(arr2, size);
    begin = clock();
    MergeSort(arr2, size);
    end = clock();
    time = double(end - begin) / (double)CLOCKS_PER_SEC;
    cout << "Merge Sort time: " << time << endl;
    //display(arr2, size);
    cout << "***** End Merge Sort *****" << endl;

/*
    cout << "***** Quick Sort *****" << endl;
    //display(arr3, size);
    begin = clock();
    QuickSort(arr3, size);
    end = clock();
    time = double(end - begin) / (double)CLOCKS_PER_SEC;
    cout << "Quick Sort time:" << time << endl;
    //display(arr3, size);
    cout << "***** End Quick Sort *****" << endl;
*/
    return 0;
}
