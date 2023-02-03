#include "../include/ByteReader.h"

ByteReader::ByteReader(const std::string &filename) :
        _file(filename, std::ios::binary) {}

uint32_t ByteReader::read_byte(int32_t length) {
    int byte;
    while (buffer_position + length > _position_read) {
        byte = _file.get();
        if (byte == EOF) break;

        tmp = tmp << 8 | (uint8_t) byte;
        _position_read += 8;
    }

    if (byte == EOF && length > (_position_read - buffer_position)) {
        return 0xffffffff;
    }

    auto return_value = tmp >> ((_position_read - buffer_position) - length);
    auto mask = 1;
    for (int i = 0; i < length; i++) {
        mask *= 2;
    }
    return_value = return_value & (mask - 1);
    buffer_position += length;
    return return_value;
}

bool ByteReader::can_be_read(int32_t len) {
    return ((len < (_position_read - buffer_position)) || ((bool) (_file)));
}