#include "../include/AVL_Tree.h"

int AVL_Tree::get_height(AVL_Tree::Node *node) {
    return (node) ? node->height : -1;
}

int AVL_Tree::get_balance_factor(AVL_Tree::Node *node) {
    return (node) ? (get_height(node->left) - get_height(node->right)) : 0;
}

void AVL_Tree::switch_parents(AVL_Tree::Node *A, AVL_Tree::Node *B) {
    if (B) B->parent = A->parent;

    if (!A->parent) root = B;
    else if (A == A->parent->left) A->parent->left = B;
    else A->parent->right = B;
}

void AVL_Tree::left_rotate(AVL_Tree::Node *A) {
    auto *B = A->right;
    A->right = B->left;

    if (B->left) B->left->parent = A;

    switch_parents(A, B);

    B->left = A;
    A->parent = B;

    A->height = 1 + std::max(get_height(A->left), get_height(A->right));
    B->height = 1 + std::max(get_height(B->left), get_height(B->right));
}

void AVL_Tree::right_rotate(AVL_Tree::Node *A) {
    auto *B = A->left;
    A->left = B->right;

    if (B->right) B->right->parent = A;

    switch_parents(A, B);

    B->right = A;
    A->parent = B;

    A->height = 1 + std::max(get_height(A->left), get_height(A->right));
    B->height = 1 + std::max(get_height(B->left), get_height(B->right));
}

void AVL_Tree::rebalance(AVL_Tree::Node *A, AVL_Tree::Node *B, AVL_Tree::Node *C) {
    if (A == C->left) {
        if (B == C->left->left) {
            right_rotate(C);
        } else if (B == C->left->right) {
            left_rotate(A);
            right_rotate(C);
        }
    } else if (A == C->right) {
        if (B == C->right->right) {
            left_rotate(C);
        } else if (B == C->right->left) {
            right_rotate(A);
            left_rotate(C);
        }
    }
}

void AVL_Tree::release_tree(AVL_Tree::Node *root) {
    if (root) {
        release_tree(root->left);
        release_tree(root->right);
        delete root;
    }
}

AVL_Tree::~AVL_Tree() {
    release_tree(root);
}

int AVL_Tree::get_node_count() const {
    return node_count;
}

void AVL_Tree::insert(uint32_t key, std::string value) {

}

AVL_Tree::Node *AVL_Tree::find(uint32_t key) const {
    Node *result = root;
    while (result && result->key != key) {
        result = (key < result->key) ? result->left : result->right;
    }
    return result;
}