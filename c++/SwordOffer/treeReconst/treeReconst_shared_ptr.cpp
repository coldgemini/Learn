#include <iostream>
#include <memory>


using namespace std;
using std::make_shared;
using std::shared_ptr;

struct Node {
    int val;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    explicit Node(int x) : val(x), left(nullptr), right(nullptr) {};
};


// can pass pointer by value
void print_tree_pre_recur(shared_ptr<Node> root) {
    if (root == nullptr)
        return;
    cout << root->val << " ";
    print_tree_pre_recur(root->left);
    print_tree_pre_recur(root->right);
};

void print_tree_pre(shared_ptr<Node> root) {
    print_tree_pre_recur(root);
    cout << endl;
}


void print_tree_in_recur(shared_ptr<Node> root) {
    if (root == nullptr)
        return;
    print_tree_in_recur(root->left);
    cout << root->val << " ";
    print_tree_in_recur(root->right);
};

void print_tree_in(shared_ptr<Node> root) {
    print_tree_in_recur(root);
    cout << endl;
};

int findRootInInOrder(int *in, int len, int val) {
    int idx = 0;
    while (idx < len) {
        if (in[idx] == val)
            return idx;
        idx++;
    }
    return 0;
}

void treeReconst(shared_ptr<Node> &root, int *pre, int *in, int len) {
    // end cond
    if (len == 0)
        return;

    // find root in in_order
    int rval = pre[0];
    int in_idx = findRootInInOrder(in, len, rval);

    root = make_shared<Node>(rval);

    // recursion
    int l_len = in_idx;
    int r_len = len - in_idx - 1;
    int *l_pre = pre + 1;
    int *l_in = in;
    int *r_pre = pre + 1 + l_len;
    int *r_in = in + 1 + l_len;
    treeReconst(root->left, l_pre, l_in, l_len);
    treeReconst(root->right, r_pre, r_in, r_len);
};


int main() {
    int pre[] = {1, 2, 4, 7, 3, 5, 6, 8};
    int pre_len = sizeof(pre) / sizeof(pre[0]);
    int in[] = {4, 7, 2, 1, 5, 3, 8, 6};
    int in_len = sizeof(in) / sizeof(in[0]);
    cout << "pre_len: " << pre_len << endl;
    cout << "in_len: " << in_len << endl;

    shared_ptr<Node> root = nullptr;
    treeReconst(root, pre, in, in_len);


    cout << "tree pre: " << endl;
    print_tree_pre(root);
    cout << "tree in: " << endl;
    print_tree_in(root);

    return 0;
}