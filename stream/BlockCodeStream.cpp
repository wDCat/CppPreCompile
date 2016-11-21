//
// Created by whmwi on 2016/11/3.
//

#include <cstring>
#include "include/BlockCodeStream.h"
#include "../util/include/helper.h"

char BlockCodeStream::read() {
    return data[position++];
}

bool BlockCodeStream::isEOF() {
    return position >= size;
}

int BlockCodeStream::reset() {
    position = 0;
    return 0;
}

BlockCodeStream::BlockCodeStream(char *data) : data(data) {
    size = strlen(this->data);
}

BlockCodeStream::BlockCodeStream(const char *data) {
    this->data = new char[BUFF_SIZE];
    sprintf(this->data, "%s", data);
    size = strlen(this->data);
}

BlockCodeStream::~BlockCodeStream() {
    if (data != nullptr)
        delete[] data;
}

