cmake_minimum_required(VERSION 3.24)
project(LZW_Compression)

set(CMAKE_CXX_STANDARD 20)

add_executable(LZW_Compression main.cpp src/DictionaryNode.cpp src/Encoder.cpp src/Trie.cpp
        src/ByteWriter.cpp src/Utils.cpp src/Decoder.cpp src/AVL_Tree.cpp src/ByteReader.cpp)
