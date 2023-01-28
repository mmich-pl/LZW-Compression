#ifndef LZW_COMPRESSION_ENCODER_H
#define LZW_COMPRESSION_ENCODER_H

#include <cstdint>
#include "DictionaryNode.h"
#include "Trie.h"
#include <fstream>

class Encoder {
private:
    uint64_t _code_size, _max_table_size;
    static uint32_t _code;

    static void init_trie(DictionaryNode *root);

public:
    Encoder();

    ~Encoder() = default;

    void encode(const std::string &filename) const;

};

#endif
