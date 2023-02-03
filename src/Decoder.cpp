#include "../include/Decoder.h"

uint32_t Decoder::_code = 0;

Decoder::Decoder() {
    _code_size = 32;
    _max_table_size = (((uint64_t) 1) << _code_size);
}

void Decoder::init_tree(AVLTree &code_tree) {
    for (_code = 0; _code <= 255; _code++)
        code_tree.insert(_code, std::string(1, (char) _code));
}

void Decoder::decode(const std::string &filename) const {
    bool is_overflow = false;
    std::string new_word;
    AVLTree code_tree;
    std::string word;

    std::string fname = filename.substr(0, filename.rfind('.'));
    std::ofstream output_file(fname, std::ios::binary);

    ByteReader byte_reader(filename);
    init_tree(code_tree);

    uint32_t code = byte_reader.read_byte(bit_size(code_tree.get_node_count()));
    word = code_tree.find(code)->value;
    size_t counter = 0;
    const char *str = word.c_str();
    for (size_t i = 0; i < word.size(); i++) {
        output_file.put(str[i]);
        counter++;
    }

    while (byte_reader.can_be_read(bit_size(code_tree.get_node_count()))) {
        code = byte_reader.read_byte(bit_size(code_tree.get_node_count() + 1));
        if (code == 0xffffffff) break;

        (code_tree.find(code) == nullptr) ? new_word = word + word[0] : new_word = code_tree.find(code)->value;
        str = new_word.c_str();
        for (size_t i = 0; i < new_word.size(); i++) {
            output_file.put(str[i]);
            counter++;
        }

        if (_code < _max_table_size && !is_overflow) {
            code_tree.insert(_code, word + new_word[0]);
            if (_code != (_max_table_size - 1)) _code++;
            else is_overflow = true;
        }
        word = new_word;
    }

    output_file.close();
}