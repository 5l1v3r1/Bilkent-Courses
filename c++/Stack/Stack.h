#include <string>
using namespace std;

class Stack {
public:
    Stack();
    Stack(const Stack &input);
    void push(string data);
    string pop();
    bool isEmpty();
    void display();
    string getTop();
private:
    struct Node{
        string data;
        Node *next;
    };
    Node *top;
};
