#include "../include/Decoder.h"

uint32_t Decoder::_code = 0;

Decoder::Decoder() {
    _code_size = 32;
    _max_table_size = (((uint64_t) 1) << _code_size);
}

void Decoder::decode(const std::string &filename) const {

}


