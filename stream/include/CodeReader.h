//
// Created by whmwi on 2016/11/3.
//

#ifndef CPPPREBUILD_CODEREADER_H
#define CPPPREBUILD_CODEREADER_H


#include <cstdio>
#include "CodeStream.h"
#include "Line.h"

class CodeReader {
private:
    CodeStream* stream;
    int nowLine=0;
public:
    CodeReader(CodeStream* stream);
    ~CodeReader();
    Line* nextLine();
    CodeStream* nextBlock(Line* nowLine);
    bool isEOF()const;
};


#endif //CPPPREBUILD_CODEREADER_H
