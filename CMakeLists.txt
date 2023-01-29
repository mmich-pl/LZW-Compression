cmake_minimum_required(VERSION 3.24)
project(LZW_Compression)

set(CMAKE_CXX_STANDARD 20)

add_executable(LZW_Compression main.cpp include/DictionaryNode.h src/DictionaryNode.cpp src/Encoder.cpp include/Encoder.h src/Trie.cpp include/Trie.h src/ByteWriter.cpp include/ByteWriter.h src/Utils.cpp include/Utils.h src/Decoder.cpp include/Decoder.h src/AVL_Tree.cpp include/AVL_Tree.h)
