#include <cassert>
#include "../include/DictionaryNode.h"

DictionaryNode::DictionaryNode(char character, uint32_t code, bool isWord) : _symbol(character), _code(code), _eow(isWord) {}

void DictionaryNode::set_code(uint32_t code) {
    _code = code;
}

void DictionaryNode::set_eow(bool eow) {
    _eow = eow;
}

char DictionaryNode::get_symbol() const {
    return _symbol;
}

uint32_t DictionaryNode::get_code() const {
    return _code;
}

bool DictionaryNode::is_eow() const {
    return _eow;
}

void DictionaryNode::add_child(DictionaryNode *node) {
    assert(_children_size < 256);
    _childrens[_children_size++] = node;
}

DictionaryNode *DictionaryNode::search_child(char character) {
    auto is_char = [&](DictionaryNode* node) {return node->get_symbol() == character;};
    auto result = std::find_if(std::begin(_childrens), std::end(_childrens), is_char);

    return (result) ?  *result:  nullptr;
}