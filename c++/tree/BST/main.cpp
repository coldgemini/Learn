#include <iostream>
#include "BST.h"

int main() {
    std::cout << "BST main:" << std::endl;
    BST tree;
    bool searchRes;
    int vmin;
    int vmax;
    int height;
    int size;
    bool isBST;

    tree.Insert(2);
    tree.Insert(4);
    tree.Insert(0);
    tree.Insert(3);
    tree.Insert(1);
    tree.PrintTreeInOrder();
    searchRes = tree.Search(2);
    std::cout << "if contains 2: " << searchRes << std::endl;
    vmin = tree.FindMin();
    vmax = tree.FindMax();
    std::cout << "min: " << vmin << std::endl;
    std::cout << "max: " << vmax << std::endl;

//    tree.ReverseOrder();

    tree.PrintTreeInOrder();
    searchRes = tree.Search(2);
    std::cout << "if contains 2: " << searchRes << std::endl;
    vmin = tree.FindMin();
    vmax = tree.FindMax();
    std::cout << "min: " << vmin << std::endl;
    std::cout << "max: " << vmax << std::endl;

    height = tree.Height();
    std::cout << "height: " << height << std::endl;

    size = tree.Size();
    std::cout << "size: " << size << std::endl;

    isBST = tree.isBST();
    std::cout << "isBST: " << isBST << std::endl;
    std::cout << "isBST: " << true << std::endl;

    std::cout << "print Tree: " << std::endl;
    tree.printTreeStruct();

    return 0;
}

