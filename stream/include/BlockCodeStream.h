//
// Created by whmwi on 2016/11/3.
//

#ifndef CPPPREBUILD_BLOCKCODESTREAM_H
#define CPPPREBUILD_BLOCKCODESTREAM_H


#include "CodeStream.h"

class BlockCodeStream : public CodeStream {
private:
    char *data = nullptr;
    size_t size = 0;
    size_t position = 0;
public:
    BlockCodeStream(char *data);

    BlockCodeStream(const char *data);

    ~BlockCodeStream();

    virtual bool isEOF() override;

    virtual char read() override;

    virtual int reset() override;
};


#endif //CPPPREBUILD_BLOCKCODESTREAM_H
