#include "linked_list.h"
#include <iostream>

int main() {
    LinkedList list0;
    list0.createnode(0);
    list0.createnode(1);
    list0.createnode(2);
    list0.insert_start(-1);
    list0.insert_start(-2);
    list0.insert_end(10);
    list0.insert_position(0, 8);
    list0.insert_position(1, 9);
    list0.insert_position(2, 10);
    list0.display();
//    list0.clear();
//    list0.display();
    list0.delete_first();
    list0.display();
    list0.delete_first();
    list0.display();
    list0.delete_last();
    list0.display();
    list0.delete_last();
    list0.display();
    list0.delete_position(2);
    list0.display();
    list0.delete_position(1);
    list0.display();
    list0.delete_position(0);
    list0.display();
    std::cout << "end" << std::endl;
}