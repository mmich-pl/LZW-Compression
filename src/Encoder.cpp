#include "../include/Encoder.h"

uint32_t Encoder::_code = 0;

Encoder::Encoder() {
    _code_size = 32;
    _max_table_size = ((uint64_t) 1) << _code_size;
}

void Encoder::init_trie(DictionaryNode *root) {
    for (_code = 0; _code <= 255; _code++)
        Trie::get_instance()->add_word(root, std::string(1, (char) _code), _code);
}

void Encoder::encode(const std::string &filename) const {

}
