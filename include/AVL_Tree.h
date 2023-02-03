#ifndef LZW_COMPRESSION_AVL_TREE_H
#define LZW_COMPRESSION_AVL_TREE_H

#include <cstdint>
#include <string>
#include <utility>

struct AVLTree {
    struct AVLNode {
        AVLNode *parent = nullptr, *left = nullptr, *right = nullptr;
        uint32_t key{};
        int height{};
        std::string value;

        AVLNode(uint32_t key, std::string value) : key(key), value(std::move(value)) {};

        AVLNode() = default;
    };

    int _node_count{};
    AVLNode *_root = nullptr;

    static int get_higher_branch(const AVLTree::AVLNode *node);

    static int get_height(const AVLNode *node);

    static int get_balance_factor(AVLNode *node);

    void switch_parents(AVLNode *A, AVLNode *B);

    void left_rotate(AVLNode *A);

    void right_rotate(AVLNode *A);

    void rebalance(AVLNode *A, AVLNode *B, AVLNode *C);

    static void release_tree(AVLNode *node);

public:

    AVLTree();

    ~AVLTree();

    int get_node_count() const;

    void insert(uint32_t key, std::string value);

    AVLNode *find(uint32_t key) const;
};

#endif
