#ifndef LZW_COMPRESSION_BYTEWRITER_H
#define LZW_COMPRESSION_BYTEWRITER_H

#include <fstream>
#include <cstdint>

class ByteWriter {
    std::ofstream _file;
    uint64_t _buffer = 0;
    uint32_t _position_write = 0, _buffer_position = 0;

public:
    explicit ByteWriter(const std::string &filename);

    ~ByteWriter() = default;

    void write_byte(uint32_t byte, int len);

    void close();
};

#endif
