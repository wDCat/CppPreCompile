//
// Created by whmwi on 2016/11/5.
//

#include <string>
#include <cstring>
#include "include/CodeWriter.h"

int CodeWriter::write(const char *line) {
    for (int x = 0; x < strlen(line); x++)write(line[x]);
    return 0;
}

int CodeWriter::write(std::string* str) {
    write(str->c_str());
    return 0;
}
int CodeWriter::write(std::string str) {
    write(str.c_str());
    return 0;
}
