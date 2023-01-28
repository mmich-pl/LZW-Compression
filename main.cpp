#include <iostream>
#include "include/Encoder.h"

bool file_exists(const std::string &name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void showUsage() {
    std::cerr <<
              "--------- LZW Compressor & Decompressor ---------\n"
              "DESCRIPTION\n"
              "\tAn application launched from the command line\n"
              "\twhich, based on passed flags, can compress\n "
              "\tor decompress given file.\n\n"
              "FLAGS:\n"
              "\t-h                    -- print help\n"
              "\t-c <path>             -- compress file\n"
              "\t-d <path>             -- decompress file\n"
              "USAGE:\n"
              "\t./main <flag> <filename>";
}

int main(int argc, char *argv[]) {
    std::string flag = argv[1];
    if (flag == "-h" || argc != 3) {
        showUsage();
        return -1;
    }

    std::string path = argv[2];

    if (!file_exists(path)) {
        std::cerr << "File: \'" << path << "\' does not exist. Check path correctness.";
        return -1;
    }

    if (flag == "-c") {
        auto *enc = new Encoder();
        std::cout << __FUNCTION__ << "(): Encrypting \'" << path << "\'...\n";
        enc->encode(path);
        std::cout << __FUNCTION__ << "(): Encrypting finished";
        delete enc;
    }
}
