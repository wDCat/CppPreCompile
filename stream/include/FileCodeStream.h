//
// Created by whmwi on 2016/11/3.
//

#ifndef CPPPREBUILD_FILECODESTREAM_H
#define CPPPREBUILD_FILECODESTREAM_H


#include <cstdio>
#include "CodeStream.h"
#include "../../util/include/exceptions.h"

class FileCodeStream : public CodeStream {
private:
    const char *path;
    FILE *file;
public:
    FileCodeStream(const char *path);

    ~FileCodeStream();

    virtual char read() override;

    virtual bool isEOF() override;
    virtual int reset() override;
};


#endif //CPPPREBUILD_FILECODESTREAM_H
