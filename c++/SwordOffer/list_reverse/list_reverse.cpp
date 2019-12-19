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


    void push_front(int value);

    void reverse();

    void display();

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

void LinkedList::reverse() {
    Node *post = head;
    Node *cur = head->next;
    Node *pre = head->next->next;
    while (cur != nullptr) {
        cur->next = post;

        post = cur;
        cur = pre;
        if (pre)
            pre = pre->next;
    }
    head->next = nullptr;
    tail = head;
    head = post;
}

int main() {
    LinkedList llist;
    llist.push_front(1);
    llist.push_front(2);
    llist.push_front(3);
    llist.push_front(4);
    llist.display();

    llist.reverse();
    llist.display();
    return 0;
}