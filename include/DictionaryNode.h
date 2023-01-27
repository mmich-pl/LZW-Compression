#ifndef LZW_COMPRESSION_DICTIONARYNODE_H
#define LZW_COMPRESSION_DICTIONARYNODE_H

#include <cstdint>
#include <algorithm>
class DictionaryNode {
private:
    char _symbol;
    uint32_t _code;
    bool _eow; //is end of word
    DictionaryNode *_childrens[256];
    uint32_t _children_size = 0; // amount of children of current node

public:
    DictionaryNode(char c = '\0', uint32_t code = 65535, bool word = false);

    ~DictionaryNode() = default;

    void add_child(DictionaryNode *child);

    void set_code(uint32_t code);

    void set_eow(bool eow);

    char get_symbol() const;

    uint32_t get_code() const;

    bool is_eow() const;

    DictionaryNode *search_child(char c);
};

#endif

