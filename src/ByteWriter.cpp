#include "../include/ByteWriter.h"

ByteWriter::ByteWriter(const std::string &filename) : _file(filename, std::ios::binary) {}

void ByteWriter::write_byte(uint32_t byte, int len)  {
    _buffer <<= len;
    _buffer |= byte;
    _buffer_position += len;

    while (_buffer_position - _position_write >= 8) {
        char byte_to_write = _buffer >> ((_buffer_position - _position_write) - 8);
        byte_to_write&= 0xff;
        _file.put(byte_to_write);
        _position_write += 8;
    }
}

void ByteWriter::close() {
    if (_buffer_position - _position_write > 0) {
        char  byte_to_write = _buffer << (8 - (_buffer_position - _position_write));
        _file.put( byte_to_write);
        _position_write += _buffer_position - _position_write;
    }
    _file.close();
}
