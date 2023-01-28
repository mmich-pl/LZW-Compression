#include "../include/Trie.h"

Trie *Trie::_trie = nullptr;

Trie::Trie() {
    _root = new DictionaryNode;
}

DictionaryNode *Trie::get_root() {
    return _root;
}

Trie *Trie::get_instance() {
    if (!_trie) _trie = new Trie;
    return _trie;
}

void Trie::delete_instance() {
    delete _trie;
    _trie = nullptr;
}

void Trie::add_word(DictionaryNode *node, std::string word, uint32_t code) {
    if (word.empty()) {
        node->create_eow_node(code);
        return;
    }

    auto symbol = word.at(0);
    auto *child = node->search_child(symbol);

    if (!child) {
        child = new DictionaryNode(symbol);
        node->add_child(child);
    }
    add_word(child, word.erase(0, 1), code);
}

DictionaryNode *Trie::search_word(DictionaryNode *node, std::string word) {
    if (word.empty())
        return (node->is_eow()) ? node : nullptr;

    char c = word.at(0);
    auto child = node->search_child(c);
    return (!child) ? nullptr : search_word(child, word.erase(0, 1));
}
