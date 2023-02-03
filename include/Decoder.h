#ifndef LZW_COMPRESSION_DECODER_H
#define LZW_COMPRESSION_DECODER_H

#include <cstdint>
#include <string>
#include <fstream>
#include "AVL_Tree.h"
#include "ByteReader.h"
#include "Utils.h"

class Decoder {
    uint64_t _code_size, _max_table_size;
    static uint32_t _code;

    static void init_tree(AVLTree &code_tree);

public:
    Decoder();

    ~Decoder() = default;

    void decode(const std::string &filename) const;
};

#endif
