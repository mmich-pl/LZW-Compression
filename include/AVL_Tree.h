#ifndef LZW_COMPRESSION_AVL_TREE_H
#define LZW_COMPRESSION_AVL_TREE_H

#include <cstdint>
#include <string>
#include <utility>

struct AVL_Tree {
private:
    struct Node {
        Node *parent = nullptr, *left = nullptr, *right=nullptr;
        uint32_t key{};
        int height{};
        std::string value{};

        Node(char32_t key, std::string value) : key(key), value(std::move(value)){};
        Node() = default;

        ~Node() = default;

        inline auto operator<=>(Node* node) const {
            return this->key <=> node->key;
        }

    };

    int _node_count{};
    Node *_root = nullptr;

    static int get_height(const Node *node);

    static int get_higher_branch (const AVL_Tree::Node *node);

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
