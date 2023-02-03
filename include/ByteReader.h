#ifndef LZW_COMPRESSION_BYTEREADER_H
#define LZW_COMPRESSION_BYTEREADER_H

#include <fstream>

class ByteReader {
    std::ifstream _file;
    uint64_t tmp=0, _position_read = 0, buffer_position = 0;

public:
    ByteReader(const std::string &filename);

    uint32_t read_byte(int32_t length);

    bool can_be_read(int32_t len);
};

#endif
