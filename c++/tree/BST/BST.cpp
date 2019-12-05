#include <iostream>
#include <algorithm>
#include "BST.h"

// node constructor
BSTNode::BSTNode(int key) : Key(key), Left(nullptr), Right(nullptr), Parent(nullptr) {}

// constructor
BST::BST() : root(nullptr) {}

BSTNode *BST::Insert(BSTNode *node, int key) {
    if (node == nullptr) {
        node = new BSTNode(key);
    } else if (key > node->Key) {
        node->Right = Insert(node->Right, key);
        node->Right->Parent = node;
    } else {
        node->Left = Insert(node->Left, key);
        node->Left->Parent = node;
    }
    // when empty, get new address
    return node;
}

void BST::Insert(int key) {
    root = Insert(root, key);
}

void BST::PrintTreeInOrder(BSTNode *node) {
    if (node == nullptr)
        return;
    PrintTreeInOrder(node->Left);
    std::cout << node->Key << " ";
    PrintTreeInOrder(node->Right);
    return;
}

void BST::PrintTreeInOrder() {
    PrintTreeInOrder(root);
    std::cout << std::endl;
    return;
}

BSTNode *BST::Search(BSTNode *node, int key) {
    if (node == nullptr)
        return nullptr;
    else if (key == node->Key)
        return node;
    else if (key < node->Key)
        return Search(node->Left, key);
    else
        return Search(node->Right, key);
}

bool BST::Search(int key) {
    BSTNode *result = Search(root, key);
    return result != nullptr;
}

int BST::FindMin(BSTNode *node) {
    if (node == nullptr)
        return -1;
    else if (node->Left == nullptr)
        return node->Key;
    else
        return FindMin(node->Left);
}

int BST::FindMax(BSTNode *node) {
    if (node == nullptr)
        return -1;
    else if (node->Right == nullptr)
        return node->Key;
    else
        return FindMax(node->Right);
}

int BST::FindMin() {
    return FindMin(root);
}

int BST::FindMax() {
    return FindMax(root);
}

void BST::ReverseOrder(BSTNode *node) {
    if (node == nullptr)
        return;
    BSTNode *tmp;
    tmp = node->Left;
    node->Left = node->Right;
    node->Right = tmp;
    ReverseOrder(node->Left);
    ReverseOrder(node->Right);
    return;
}

void BST::ReverseOrder() {
    return ReverseOrder(root);
}

int BST::Height(BSTNode *node) {
    if (node == nullptr)
        return 0;
    else
        return 1 + std::max(Height(node->Left), Height(node->Right));
}

int BST::Height() {
    return Height(root);
}

int BST::Size(BSTNode *node) {
    if (node == nullptr)
        return 0;
    else
        return 1 + Size(node->Left) + Size(node->Right);
}

int BST::Size() {
    return Size(root);
}

bool BST::isBST(BSTNode *node) {
    if (node == nullptr)
        return true;
    if (node->Left != nullptr && node->Key <= node->Left->Key)
        return false;
    if (node->Right != nullptr && node->Key >= node->Right->Key)
        return false;
    return isBST(node->Left) && isBST(node->Right);
}

bool BST::isBST() {
    return isBST(root);
}

void BST::printTreeStruct() {
    if (root == nullptr)
        return;
    int his_height = Height();
    int cur_height = 0;
    BSTQueue.push(root);
    BSTNode *p_node;
    while (!BSTQueue.empty()) {
        p_node = BSTQueue.front();
        BSTQueue.pop();
        cur_height = Height(p_node);
        if (cur_height != his_height) {
            his_height = cur_height;
            std::cout << std::endl;
        }
        std::cout << p_node->Key << " ";
        if (p_node->Left != nullptr)
            BSTQueue.push(p_node->Left);
        if (p_node->Right != nullptr)
            BSTQueue.push(p_node->Right);
    }
}
