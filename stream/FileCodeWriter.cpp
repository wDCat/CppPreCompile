//
// Created by whmwi on 2016/11/7.
//

#include "include/FileCodeWriter.h"
#include "../util/include/exceptions.h"

int FileCodeWriter::write(int byte) {
    fputc(byte, file);
}

int FileCodeWriter::flush() {
    fflush(file);
}

int FileCodeWriter::close() {
    fclose(file);
}

FileCodeWriter::FileCodeWriter(const std::string &path) : path(path) {
    file = fopen(path.c_str(), "wb+");
    if (file == NULL)
        throw IOException("fail to open output file.", path);
}
