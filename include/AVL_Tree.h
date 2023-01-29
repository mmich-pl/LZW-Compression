#ifndef LZW_COMPRESSION_AVL_TREE_H
#define LZW_COMPRESSION_AVL_TREE_H

#include <cstdint>
#include <string>

struct AVL_Tree {
private:
    struct Node {
        Node *parent{}, *left{}, *right{};
        uint32_t key{}, height{};
        std::string value{};

        Node() = default;

        ~Node() = default;
    };

};
#endif
