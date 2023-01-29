#ifndef LZW_COMPRESSION_AVL_TREE_H
#define LZW_COMPRESSION_AVL_TREE_H

#include <cstdint>
#include <string>

struct AVL_Tree {
private:
    struct Node {
        Node *parent{}, *left{}, *right{};
        uint32_t key{};
        int height{};
        std::string value{};

        Node() = default;

        ~Node() = default;

        inline auto operator<=>(uint32_t key) const{
            return this->key <=> key;
        }

    };

    int node_count{};
    Node *root = nullptr;

    static int get_height(Node *node);

    static int get_balance_factor(Node *node);

    void switch_parents(Node *A, Node *B);

    void left_rotate(Node *A);

    void right_rotate(Node *A);

    void rebalance(Node *A, Node *B, Node *C);

    static void release_tree(Node *root);

public:
    AVL_Tree() = default;

    ~AVL_Tree();

    int get_node_count() const;

    void insert(uint32_t key, std::string value);

    Node *find(uint32_t) const;


};

#endif
