//
// Created by whmwi on 2016/11/3.
//

#ifndef CPPPREBUILD_LINE_H
#define CPPPREBUILD_LINE_H


#include <string>
#include <ostream>
#include "../../util/include/helper.h"

class Line {
private:
    char *txt;
public:
    Line(char *txt) : txt(txt) {

    }

    Line(const char *txt) {
        this->txt = (char *) malloc(sizeof(char) * BUFF_SIZE);
        sprintf(this->txt, "%s", txt);
    }

    Line(std::string txt) {
        Line(txt.c_str());
    }

    ~Line() {
        if (txt != nullptr)
            delete[] txt;
    }

    static char *trim(char *data);

    static char *trim(const char *data);

    static bool removeNotes(char *&data, bool &ignore);

    char *trim();

    char *removeNotes();

    char *getText() const {
        return txt;
    }

    friend std::ostream &operator<<(std::ostream &os, const Line &line);
};


#endif //CPPPREBUILD_LINE_H
