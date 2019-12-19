#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;

    Node(int data) : data(data), next(nullptr) {};
};

class LinkedList {
private:
    Node *head, *tail;
    int size;
public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {};

    LinkedList(LinkedList a, LinkedList b);

    void push_front(int value);


    void display();

    Node *get_head() { return head; };
};

void LinkedList::push_front(int value) {
    Node *temp = new Node(value);
    if (head == nullptr) {
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void LinkedList::display() {
    Node *temp;
    temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

LinkedList::LinkedList(LinkedList a, LinkedList b) {
    cout << "constr" << endl;
    head = nullptr;
    tail = nullptr;
    size = 0;

    Node *ha = a.get_head();
    Node *hb = b.get_head();

    int val = 0;
    while (ha && hb) {
        cout << "push " << endl;
        if (ha->data <= hb->data) {
            val = ha->data;
            push_front(val);
            ha = ha->next;
        } else {
            val = hb->data;
            push_front(val);
            hb = hb->next;
        }
    }

    while (ha) {
        val = ha->data;
        push_front(val);
        ha = ha->next;
    }
    while (hb) {
        val = hb->data;
        push_front(val);
        hb = hb->next;
    }
}

int main() {
    LinkedList a;
    a.push_front(1);
    a.push_front(3);
    a.push_front(5);
    a.push_front(7);
    a.push_front(12);
    a.display();

    LinkedList b;
    b.push_front(2);
    b.push_front(4);
    b.push_front(6);
    b.push_front(8);
    b.push_front(9);
    b.push_front(10);
    b.display();

    LinkedList merge(a, b);

    merge.display();
    return 0;
}