#include <cassert>
#include <iostream>
#include "../include/DictionaryNode.h"

DictionaryNode::DictionaryNode(char c, uint32_t code, bool is_eow) : _symbol(c), _code(code), _eow(is_eow) {
    _childrens.reserve(256);
}

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
    assert(_children_size <= 256);
    _children_size++;
    _childrens.push_back(node);
}

DictionaryNode *DictionaryNode::search_child(char character) {
    auto is_char = [&](DictionaryNode* node) {return node && *node == character;};
    auto result = std::find_if(_childrens.begin(), _childrens.end(),is_char);
    return (result != _childrens.end()) ? *result : nullptr;
}

void DictionaryNode::create_eow_node(uint32_t code) {
    this->set_code(code);
    this->set_eow(true);
}