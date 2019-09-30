class ArrayQueue {
public:
    ArrayQueue(int size);
    ArrayQueue(const ArrayQueue &input);
    ~ArrayQueue();
    void dequeue();
    void enqueue(const int item);
    int peekFront() const;
    bool isEmpty() const;
    bool isFull() const;
    void display();
private:
    int size;
    int front;
    int back;
    int itemNumber;
    int *queue;
};
