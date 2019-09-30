class Queue {
public:
    Queue();
    Queue(Queue &input);
    void dequeue();
    void enqueue(int data);
    bool isEmpty();
    void display();
private:
    struct Node {
        int data;
        Node *next;
    };
    Node *first;
    Node *last;
};
