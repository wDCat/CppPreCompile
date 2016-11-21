//
// Created by whmwi on 2016/11/3.
//

#ifndef CPPPREBUILD_EXCEPTIONS_H
#define CPPPREBUILD_EXCEPTIONS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <exception>
#include "dlog.h"

class Exception : private std::exception {
protected:
    std::string msg;
public:
    Exception() {
        this->print();
    }

    Exception(std::string msg) {
        this->msg = msg;
        this->print();
    }

    void print() {
        derr << this->what() << std::endl;
    }

    const char *what() {
        return msg.c_str();
    }
};

class IOException : public Exception {
public:

    IOException(std::string msg, std::string fn = "unknown") {
        this->msg = "IOException:" + msg + " (file:" + fn + ")";
        this->print();
    }
};

class BuildException : public Exception {
public:
    BuildException(std::string msg, std::string line) {
        this->msg = "BuildException:" + msg + " (line:" + line + ")";
        this->print();
    }
};


#endif //CPPPREBUILD_EXCEPTIONS_H
