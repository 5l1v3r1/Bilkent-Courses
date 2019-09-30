#include "ArrayQueue.h"
#include <iostream>
using namespace std;

ArrayQueue::ArrayQueue(int size) {
    this -> size = size;
    queue = new int[size];
    for (int i = 0; i < size; i++)
        queue[i] = 0;
    front = 0;
    back = size - 1;
    itemNumber = 0;
}

ArrayQueue::ArrayQueue(const ArrayQueue &input) {
    size = input.size;
    queue = new int[size];
    for(int i = 0; i < size; i++)
        queue[i] = input.queue[i];
    front = input.front;
    back = input.back;
    itemNumber = input.itemNumber;
}

ArrayQueue::~ArrayQueue(){
    delete queue;
}

void ArrayQueue::dequeue() {
    if (!isEmpty()) {
        queue[front] = 0;
        front = (front + 1) % size;
        itemNumber --;
    }
}

void ArrayQueue::enqueue(int item) {
    if (!isFull()) {
        back = (back + 1) % size;
        queue[back] = item;
        itemNumber ++;
    }
}

int ArrayQueue::peekFront() const {
    return queue[front];
}

bool ArrayQueue::isEmpty() const {
    return itemNumber == 0;
}

bool ArrayQueue::isFull() const {
    return itemNumber >= size;
}

void ArrayQueue::display() {
    if (back == front){
        if (queue[front] != 0)
            cout << queue[front];
    }
    else if (back < front) {
        for(int i = front; i < size; i++) {
            if (queue[i] != 0)
                cout << queue[i] << " ";
        }
        for(int i = 0; i <= back; i++) {
            if (queue[i] != 0)
                cout << queue[i] << " ";
        }
    }
    else {
        for(int i = front; i <= back; i++){
            if (queue[i] != 0)
                cout << queue[i] << " ";
        }
    }
    cout << endl;
}
