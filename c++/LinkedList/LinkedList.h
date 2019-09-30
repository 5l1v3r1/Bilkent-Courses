
struct Node {
    int data;
    Node *next;
};

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList &input);
    void insert(int data);
    void remove(int data);
    void display();
    void reverse();
private:

    Node *head;
};
