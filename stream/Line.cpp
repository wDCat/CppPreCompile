//
// Created by whmwi on 2016/11/3.
//

#include <cstdio>
#include <cstring>
#include "include/Line.h"
#include "../util/include/exceptions.h"
#include "../include/pBuild.h"

char *Line::trim() {
    char *str = this->txt;
    char *str_last, *str_cur;
    if (str == NULL)
        throw Exception("trim null string");
    if (strlen(this->txt) == 0)return this->txt;
    for (; *str == 0x20 || *str == '\t'; ++str);
    for (str_last = str_cur = str; *str_cur != '\0'; ++str_cur)
        if (*str_cur != 0x20 && *str_cur != '\t')
            str_last = str_cur;
    *++str_last = 0;
    this->txt = str;
    return str;
}

char *Line::removeNotes() {
    char *ptxt = this->txt;
    if (this->txt == NULL)
        throw Exception("removeNotes null string");
    if (strlen(this->txt) == 0)return this->txt;
    for (; *ptxt != '\0'; ptxt++) {
        if (*ptxt == '/' && *(ptxt + 1) == '/') {
            *ptxt = '\0';
            break;
        } else if (*ptxt == '/' && *(ptxt + 1) == '*') {
            *ptxt = '\0';
            break;
        }
    }
    return this->txt;
}

std::ostream &operator<<(std::ostream &os, const Line &line) {
    os << "txt: " << line.txt;
    return os;
}

char *Line::trim(const char *data) {
    char* buff=new char[strlen(data)];
    sprintf(buff,"%s",data);
    return trim(buff);
}

char *Line::trim(char *data) {
    char *str = data;
    char *str_last, *str_cur;
    if (str == nullptr)
        throw Exception("trim null string");
    if (strlen(data) == 0)return data;
    for (; *str == 0x20 || *str == '\t'; ++str);
    for (str_last = str_cur = str; *str_cur != '\0'; ++str_cur)
        if (*str_cur != 0x20 && *str_cur != '\t')
            str_last = str_cur;
    *++str_last = 0;
    return str;
}

bool Line::removeNotes(char *&data, bool &ignore) {
    char *ptxt = data;
    if (ptxt == nullptr)
        throw Exception("removeNotes for null string");
    if (strlen(data) == 0)return 0;
    int zs = pBuild::find_unmirr_char(data, '/', 0);
    if (zs < 0 || zs == strlen(data))
        return ignore;
    if (ptxt[zs + 1] == '/') {
        ptxt[zs] = '\0';
    }
    int zEnd;
    int zP = -1;
    bool p = ignore;
    while (true) {
        zEnd = pBuild::find_unmirr_char(data, '*', zP + 1);
        if (zEnd < 0 || zEnd == strlen(data)) {
            ignore = p;
            return ignore;
        }
        if (zEnd > 0 && data[zEnd - 1] == '/') {
            p = true;
        }
        if (data[zEnd + 1] == '/') {
            if (p) {
                for (int x = zP - 1; x <= zEnd + 1; x++)data[x] = 0x20;
            }
            p = false;
        }
        zP = zEnd;
    }
}
