#ifndef LIST_LINKED_LIST_H
#define LIST_LINKED_LIST_H

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

    void createnode(int value);

    void display();

    void insert_start(int value);

    void insert_end(int value);

    void insert_position(int pos, int value);

    void delete_first();

    void delete_last();

    void delete_position(int pos);

    void clear();
};


#endif //LIST_LINKED_LIST_H
