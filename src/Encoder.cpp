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
    auto is_overflow = false;
    char symbol;
    std::string word, new_word;
    DictionaryNode *node;
    std::ifstream file;
    auto fname = filename + std::string(".lzw");
    auto trie = Trie::get_instance();

    file.open(filename.c_str(), std::ios::binary|std::ios::out);
    ByteWriter byte_writer(fname);

    auto *root = trie->get_root();
    init_trie(root);

    while (file.get(symbol)) {
        new_word = word + symbol;

        if (trie->search_word(root, new_word)) {
            word = new_word;
        } else {
            node = trie->search_word(root, word);
            byte_writer.write_byte(node->get_code(), bit_size(_code));

            if (_code < _max_table_size && !is_overflow) {
                trie->add_word(root, new_word, _code);
                if (_code != (_max_table_size - 1)) _code++;
                else is_overflow = true;
            }
            word = symbol;
        }
    }

    node = trie->search_word(root, word);
    byte_writer.write_byte(node->get_code(), bit_size(_code));

    Trie::delete_instance();
    file.close();
    byte_writer.close();
}
