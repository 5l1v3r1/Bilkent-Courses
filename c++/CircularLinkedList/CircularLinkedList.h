class CircularLinkedList {
public:
    CircularLinkedList();
    CircularLinkedList(const CircularLinkedList &input);
    void insert(int data);
    void remove(int data);
    void display();
private:
    struct Node {
        int data;
        Node *next;
    };
    Node *tail;
};
