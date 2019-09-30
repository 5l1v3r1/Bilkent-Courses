//
// Created by Boran Yildirim on 18.10.2016.
//
#include "sorting.h"
#include <iostream>

using namespace std;

long selectionCount;
long quickCount;
long mergeCount;

void InsertionSort (int *theArray, int n) {
    for (int i = 1; i < n; i++) {
        int nexti = theArray[i];
        int loc = i;
        while (loc > 0 && theArray[loc - 1] > nexti) {
            theArray[loc] = theArray[loc - 1];
            loc--;
        }
        theArray[loc] = nexti;
    }
}



int findMin(int theArray[], int size) {
    int index = 0;
    for (int i = 1; i < size; i++) {
        selectionCount++;
        if (theArray[i] < theArray[index]){
            selectionCount++;
            index = i;
        }
    }
    return index;
}

void SelectionSort (int *theArray, int n) {
    selectionCount = 0;
    for(int last = n - 1; last >= 1; last--) {
        selectionCount++;
        int min = findMin(theArray, last + 1);
        swap(theArray[min], theArray[last]);
    }
    cout << "Selection Sort comparison count: " << selectionCount << endl;
}

/*
void bubbleSort (int *theArray, int n) {
    bool sorted = false;
    int pass = 1;
    while (!sorted && (pass < n)) {
        sorted = true;
        for (int i = 0; i < n - pass; i++) {
            int nexti = i + 1;
            if (theArray[i] > theArray[nexti]) {
                swap(theArray[i], theArray[nexti]);
                sorted = false;
            }
        }
        pass++;
    }
}
*/

void merge (int *theArray, int first, int mid, int last) {
    int tmp[last + 1];
    int f1 = first;
    int l1 = mid;
    int f2 = mid + 1;
    int l2 = last;

    int index = f1;
    while ((f1 <= l1) && (f2 <= l2)) {
        mergeCount++;
        if (theArray[f1] > theArray[f2]) {
            mergeCount++;
            tmp[index] = theArray[f1];
            f1++;
        }
        else {
            mergeCount++;
            tmp[index] = theArray[f2];
            f2++;
        }
        index++;
    }

    while (f1 <= l1) {
        mergeCount++;
        tmp[index] = theArray[f1];
        f1++;
        index++;
    }
    while (f2 <= l2) {
        mergeCount++;
        tmp[index] = theArray[f2];
        f2++;
        index++;
    }

    for (index = first; index <= last; index++)
        theArray[index] = tmp[index];
}

void r_mergeSort (int *theArray, int first, int last) {
    if (first < last) {
        mergeCount++;
        int mid = first + (last - first) / 2;
        r_mergeSort(theArray, first, mid);
        r_mergeSort(theArray, mid + 1, last);
        merge(theArray, first, mid, last);
    }
}

void MergeSort (int *theArray, int n) {
    mergeCount = 0;
    r_mergeSort(theArray, 0, n - 1);
    cout << "Merge Sort comparison count: " << mergeCount << endl;
}


void partition(int *theArray, int first, int last, int &pivoti) {
    int piv = theArray[first];
    int ls1 = first;    //last item in S1
    int fuk = first + 1;    // fuk --> First UnKnown

    for (; fuk <= last; fuk++) {
        quickCount++;
        if (theArray[fuk] >= piv) {
            quickCount++;
            ls1++;
            swap(theArray[fuk], theArray[ls1]);
        }
    }
    swap(theArray[first], theArray[ls1]);
    pivoti = ls1;
}

void r_quickSort(int *theArray, int first, int last) {
    int pivoti;
    if (first < last) {
        quickCount++;
        partition(theArray, first, last, pivoti);
        r_quickSort(theArray, first, pivoti - 1);
        r_quickSort(theArray, pivoti + 1, last);
    }
}

void QuickSort (int *theArray, int n) {
    quickCount = 0;
    r_quickSort(theArray, 0, n - 1);
    cout << "Quick Sort comparison count: " << quickCount << endl;
}


void display (int *theArray, int n) {
    for (int i = 0; i < n; i++)
        cout << theArray[i] << " ";
    cout << endl;
}
