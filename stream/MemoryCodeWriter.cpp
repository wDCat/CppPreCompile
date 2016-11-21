//
// Created by whmwi on 2016/11/7.
//

#include <cstdlib>
#include <cstring>
#include "include/MemoryCodeWriter.h"
#include "../util/include/helper.h"
#include "../util/include/exceptions.h"

int MemoryCodeWriter::write(int byte) {
    if (size >= maxSize)throw IOException("Out of memory");
    area[size++] = byte;
}


int MemoryCodeWriter::flush() {
    return 0;
}

int MemoryCodeWriter::close() {
    return 0;
}

void MemoryCodeWriter::toFileCodeWriter(CodeWriter *writer) {
    for (int x = 0; x < size; x++)
        writer->write(area[x]);
}

int MemoryCodeWriter::alloc() {
    area = (char *) malloc(sizeof(char) * maxSize);
}

MemoryCodeWriter::MemoryCodeWriter() {
    maxSize = BUFF_SIZE;
    alloc();
}

MemoryCodeWriter::MemoryCodeWriter(int maxSize) : maxSize(maxSize) {
    alloc();

}

MemoryCodeWriter::~MemoryCodeWriter() {
    delete[] area;
}
