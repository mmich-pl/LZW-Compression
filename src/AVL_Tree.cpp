#include <iostream>
#include <utility>
#include "../include/AVL_Tree.h"

int AVLTree::get_height(const AVLTree::AVLNode *node) {
    return (node) ? node->height : -1;
}

int AVLTree::get_higher_branch(const AVLTree::AVLNode *node) {
    return std::max(get_height(node->left), get_height(node->right));
}

int AVLTree::get_balance_factor(AVLTree::AVLNode *node) {
    return (!node) ? 0 : (get_height(node->left) - get_height(node->right));
}

void AVLTree::switch_parents(AVLNode *A, AVLNode *B) {
    if (B) B->parent = A->parent;

    if (!A->parent) _root = B;
    else if (A == A->parent->left) A->parent->left = B;
    else A->parent->right = B;
}

void AVLTree::left_rotate(AVLTree::AVLNode *A) {
    AVLNode *B = A->right;
    A->right = B->left;

    if (B->left) B->left->parent = A;

    switch_parents(A, B);

    B->left = A;
    A->parent = B;

    A->height = 1 + get_higher_branch(A);
    B->height = 1 + get_higher_branch(B);
}

void AVLTree::right_rotate(AVLTree::AVLNode *A) {
    AVLNode *B = A->left;
    A->left = B->right;

    if (!B->right) B->right->parent = A;

    switch_parents(A, B);

    B->right = A;
    A->parent = B;

    A->height = 1 + get_higher_branch(A);
    B->height = 1 + get_higher_branch(B);
}

void AVLTree::rebalance(AVLNode *A, AVLNode *B, AVLNode *C) {
    if (A == C->left) {
        if (B == C->left->left)
            right_rotate(C);
        else if (B == C->left->right) {
            left_rotate(A);
            right_rotate(C);
        }
    } else if (A == C->right) {
        if (B == C->right->right) left_rotate(C);
        else if (B == C->right->left) {
            right_rotate(A);
            left_rotate(C);
        }
    }
}

void AVLTree::release_tree(AVLTree::AVLNode *node) {
    if (node) {
        release_tree(node->left);
        release_tree(node->right);
        delete node;
    }
}

AVLTree::AVLTree() = default;

AVLTree::~AVLTree() {
    release_tree(_root);
}

int AVLTree::get_node_count() const {
    return _node_count;
}

void AVLTree::insert(uint32_t key, std::string value) {
    if (find(key)) {
        std::cout << "AVLNode o tej wartości (" << key << ") już istnieje w drzewie.\n";
        return;
    }
    AVLNode *new_node = new AVLNode(key, std::move(value)),
            *temp = _root, *curr_node = nullptr, *z = new_node;

    while (temp) {
        curr_node = temp;
        (new_node->key < temp->key) ? temp = temp->left : temp = temp->right;
    }
    new_node->parent = curr_node;

    if (!curr_node)
        _root = new_node;
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

AVLTree::AVLNode *AVLTree::find(uint32_t key) const {
    AVLNode *node = _root;
    while (node && node->key != key)
        node = (key < node->key) ? node->left : node->right;
    return node;
}