//
// Created by whmwi on 2016/11/3.
//

#include "include/FileCodeStream.h"

char FileCodeStream::read() {
    if (file == NULL)return -1;
    char *p = new char[1];
    fread(p, 1, 1, file);
    char result = *p;
    free(p);
    return result;
}

bool FileCodeStream::isEOF() {
    if (file == NULL)
        return true;
    return feof(file) != 0;
}

int FileCodeStream::reset() {
    return fseek(file,0,SEEK_SET);
}

FileCodeStream::FileCodeStream(const char *path) : path(path) {
    file = fopen(path, "r");
    if (file == NULL)
        throw IOException("fail to open file", path);
}

FileCodeStream::~FileCodeStream() {
    if (file != NULL)
        fclose(file);
}

