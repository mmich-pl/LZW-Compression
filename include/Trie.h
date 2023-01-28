#ifndef LZW_COMPRESSION_TRIE_H
#define LZW_COMPRESSION_TRIE_H

#include "DictionaryNode.h"

class Trie {
private:
    DictionaryNode *_root;
    static Trie *_trie;

    Trie();

    ~Trie() = default;

public:
    DictionaryNode *get_root();

    static Trie *get_instance();

    static void delete_instance();

    void add_word(DictionaryNode *node, std::string word, uint32_t code);

    DictionaryNode *search_word(DictionaryNode *node, std::string word);
};

#endif
