//
// Created by whmwi on 2016/11/7.
//

#ifndef CPPPREBUILD_MEMORYCODEWRITER_H
#define CPPPREBUILD_MEMORYCODEWRITER_H


#include "CodeWriter.h"

class MemoryCodeWriter : public CodeWriter {
    int size=0, maxSize;
    char *area;
    int alloc();
public:
    MemoryCodeWriter();

    MemoryCodeWriter(int maxSize);

    virtual ~MemoryCodeWriter();

    virtual int write(const int byte) override;
    virtual int flush() override;

    virtual int close() override;

    void toFileCodeWriter(CodeWriter* writer);
};


#endif //CPPPREBUILD_MEMORYCODEWRITER_H
