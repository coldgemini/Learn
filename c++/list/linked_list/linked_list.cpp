#include "linked_list.h"
#include <iostream>

void LinkedList::createnode(int value) {
    Node *temp = new Node(value);
//    temp->data = value;
//    temp->next = nullptr;

    if (head == nullptr) {
        head = temp;
        tail = temp;
//        temp = nullptr;
    } else {
        tail->next = temp;
        tail = temp;
//        temp = nullptr;
    }
}

void LinkedList::display() {
//    Node *temp = new Node;
    Node *temp;
    temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << "\t";
        temp = temp->next;
    }
    std::cout << std::endl;
}

void LinkedList::insert_start(int value) {
    Node *temp = new Node(value);
    temp->next = head;
    head = temp;
}

void LinkedList::insert_end(int value) {
    Node *temp = new Node(value);
    tail->next = temp;
    tail = temp;
}

void LinkedList::insert_position(int pos, int value) {
    Node *temp = new Node(value);

    Node *cur;
    cur = head;

    // find location
    for (int i = 0; i < pos; i++) {
        cur = cur->next;
    }

    // insert
    temp->next = cur->next;
    cur->next = temp;

    // swap
    int vtmp;
    vtmp = cur->data;
    cur->data = temp->data;
    temp->data = vtmp;
}

void LinkedList::delete_first() {
    Node *temp;
    temp = head;
    head = head->next;
    delete temp;
}

void LinkedList::delete_last() {
    // Todo: bad case when only one node
    Node *current;
    Node *previous;
    current = head;
    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }
    tail = previous;
    previous->next = nullptr;
    delete current;
}

void LinkedList::delete_position(int pos) {
    // Todo: bad case when deleting first node
    Node *current;
    Node *previous;
    previous = head;
    current = head;
    for (int i = 0; i < pos; i++) {
        previous = current;
        current = current->next;
    }
    if (previous == current) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    delete current;
}

void LinkedList::clear() {
    Node *current;
    Node *tmp;
    current = head;
    while (current != nullptr) {
        tmp = current;
        current = current->next;
        delete tmp;
    }
    head = nullptr;
    tail = nullptr;
}
