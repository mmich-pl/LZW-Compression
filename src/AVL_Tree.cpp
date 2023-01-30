#include <iostream>
#include <utility>
#include "../include/AVL_Tree.h"

int AVL_Tree::get_height(const AVL_Tree::Node *node) {
    return (node) ? node->height : -1;
}

int AVL_Tree::get_higher_branch(const AVL_Tree::Node *node) {
    return std::max(get_height(node->left), get_height(node->right));
}

int AVL_Tree::get_balance_factor(AVL_Tree::Node *node) {
    return (node) ? (get_height(node->left) - get_height(node->right)) : 0;
}

void AVL_Tree::switch_parents(AVL_Tree::Node *A, AVL_Tree::Node *B) {
    if (B) B->parent = A->parent;

    if (!A->parent) _root = B;
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

    A->height = 1 + get_higher_branch(A);
    B->height = 1 + get_higher_branch(B);
}

void AVL_Tree::right_rotate(AVL_Tree::Node *A) {
    auto *B = A->left;
    A->left = B->right;

    if (B->right) B->right->parent = A;

    switch_parents(A, B);

    B->right = A;
    A->parent = B;

    A->height = 1 + get_higher_branch(A);
    B->height = 1 + get_higher_branch(B);
}

void AVL_Tree::rebalance(AVL_Tree::Node *A, AVL_Tree::Node *B, AVL_Tree::Node *C) {
    if (A == C->left) {
        if (B == C->left->left) {
            right_rotate(C);
        } else {
            left_rotate(A);
            right_rotate(C);
        }
    } else if (A == C->right) {
        if (B == C->right->right) {
            left_rotate(C);
        } else {
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
    release_tree(_root);
}

int AVL_Tree::get_node_count() const {
    return _node_count;
}

void AVL_Tree::insert(uint32_t key, std::string value) {
    if (find(key)) {
        std::cout << "AVLNode o tej wartości (" << key << ") już istnieje w drzewie.\n";
        return;
    }

    Node *new_node = new Node(key, std::move(value)), *temp = _root, *curr_node = nullptr, *z = new_node;

    while (temp) {
        curr_node = temp;
        (new_node < temp) ? temp = temp->left : temp = temp->right;
    }
    new_node->parent = curr_node;

    if (!curr_node) _root = new_node;
    else if (new_node->key < curr_node->key) curr_node->left = new_node;
    else curr_node->right = new_node;

    while (curr_node) {
        curr_node->height = 1 + get_higher_branch(curr_node);
        temp = curr_node->parent;

        if (get_balance_factor(temp) <= -2 || get_balance_factor(temp) >= 2) {
            rebalance(curr_node, z, temp);
            break;
        }

        curr_node = curr_node->parent;
        z = z->parent;
    }

    _node_count++;
}

AVL_Tree::Node *AVL_Tree::find(uint32_t key) const {
    Node *result = _root;
    while (result && result->key != key) {
        result = (key < result->key) ? result->left : result->right;
    }
    return result;
}

