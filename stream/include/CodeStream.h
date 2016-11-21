//
// Created by whmwi on 2016/11/3.
//

#ifndef CPPPREBUILD_CODESTREAM_H
#define CPPPREBUILD_CODESTREAM_H


class CodeStream {
public:
    virtual char read()=0;
    virtual bool isEOF()=0;
    virtual int reset()=0;
};


#endif //CPPPREBUILD_CODESTREAM_H
