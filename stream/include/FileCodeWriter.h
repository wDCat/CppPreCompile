//
// Created by whmwi on 2016/11/7.
//

#ifndef CPPPREBUILD_FILECODEWRITER_H
#define CPPPREBUILD_FILECODEWRITER_H


#include "CodeWriter.h"

class FileCodeWriter : public CodeWriter {
private:
    FILE* file;
    std::string path;
public:
    FileCodeWriter(const std::string &path);

    virtual int write(const int byte) override;

    virtual int flush() override;

    virtual int close() override;
};


#endif //CPPPREBUILD_FILECODEWRITER_H
