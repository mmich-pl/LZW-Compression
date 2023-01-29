#ifndef LZW_COMPRESSION_DECODER_H
#define LZW_COMPRESSION_DECODER_H

#include <cstdint>
#include <string>

class Decoder {
    private:
    uint64_t _code_size, _max_table_size;
    static uint32_t _code;

public:
    Decoder();
    ~Decoder()=default;
    void decode(const std::string &filename) const;
};

#endif
