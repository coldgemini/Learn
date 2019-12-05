//
// Created by xiang on 19-7-15.
//

#ifndef TREE_BST_H
#define TREE_BST_H

#include <queue>

class BSTNode {
public:
    int Key;
    BSTNode *Left;
    BSTNode *Right;
    BSTNode *Parent;

    BSTNode(int key);
};

class BST {
    BSTNode *root;
    std::queue<BSTNode *> BSTQueue;
public:
    BST();

    BSTNode *Insert(BSTNode *node, int key);

    void Insert(int key);

    void PrintTreeInOrder(BSTNode *node);

    void PrintTreeInOrder();

    BSTNode *Search(BSTNode *node, int key);

    bool Search(int key);

    int FindMin(BSTNode *node);

    int FindMax(BSTNode *node);

    int FindMin();

    int FindMax();

    void ReverseOrder(BSTNode *node);

    void ReverseOrder();

    int Height(BSTNode *node);

    int Height();

    int Size(BSTNode *node);

    int Size();

    bool isBST(BSTNode *node);

    bool isBST();

    void printTreeStruct();
};

#endif //TREE_BST_H
