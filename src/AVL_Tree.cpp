#include "../include/AVL_Tree.h"

int AVL_Tree::get_height(AVL_Tree::Node *node) {
    return (node) ? node->height:-1;
}

int AVL_Tree::get_balance_factor(AVL_Tree::Node *node) {
    return (node) ? (get_height(node->left) - get_height(node->right)) : 0;
}

void AVL_Tree::switch_parents(AVL_Tree::Node *A, AVL_Tree::Node *B) {

}

void AVL_Tree::left_rotate(AVL_Tree::Node *A) {

}

void AVL_Tree::right_rotate(AVL_Tree::Node *A) {

}

void AVL_Tree::rebalance(AVL_Tree::Node *A, AVL_Tree::Node *B, AVL_Tree::Node *C) {

}

void AVL_Tree::release_tree(AVL_Tree::Node *root) {
    if(root){
        release_tree(root ->left);
        release_tree(root ->right);
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