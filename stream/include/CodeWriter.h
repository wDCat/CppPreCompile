//
// Created by whmwi on 2016/11/5.
//

#ifndef CPPPREBUILD_CODEWRITER_H
#define CPPPREBUILD_CODEWRITER_H

#include <string>

class CodeWriter {
public:
    virtual int write(const int byte)=0;

    int write(const char *line);

    int write(std::string *str);
    int write(std::string str);

    virtual int flush()=0;

    virtual int close()=0;

};


#endif //CPPPREBUILD_CODEWRITER_H
