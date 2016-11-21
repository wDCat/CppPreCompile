//
// Created by whmwi on 2016/11/3.
//

#include <vector>
#include "include/CodeReader.h"
#include "include/BlockCodeStream.h"

CodeReader::CodeReader(CodeStream *stream) : stream(stream) {

}

CodeReader::~CodeReader() {
    //delete stream;
}

Line *CodeReader::nextLine() {
    if (isEOF())return nullptr;
    char pstr, *linebuff = new char[BUFF_SIZE];
    int count = 0;
    while (true) {
        if (isEOF())break;
        pstr = stream->read();
        if (pstr == '\310')continue;//神秘力量
        if (pstr == ';') { break; }
        if (pstr == '\n') {
            if (count > 3
                && ((linebuff[count - 1] == '\r' && linebuff[count - 2] == '\\')
                    || linebuff[count - 1] == '\\')) {
                if (linebuff[count - 1] == '\r') {
                    count -= 2;
                } else {
                    count -= 1;
                }
                continue;
            } else break;

        }
        linebuff[count++] = pstr;
    }
    if (linebuff[count - 1] == '\r')
        linebuff[count - 1] = '\0';
    else
        linebuff[count] = '\0';
    return new Line(linebuff);
}

bool CodeReader::isEOF() const {
    return stream->isEOF();
}

CodeStream *CodeReader::nextBlock(Line *nowLine) {
    //Unnecessary
}
