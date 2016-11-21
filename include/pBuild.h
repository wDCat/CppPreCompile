//
// Created by whmwi on 2016/11/3.
//

#ifndef CPPPREBUILD_PBUILD_H
#define CPPPREBUILD_PBUILD_H

#define BUILD_IGNORE 12
#define BUILD_DONE 9
#define BUILD_ERR 0
typedef unsigned int b_stat;

#include "../struct/BuildVal.h"
#include "../stream/include/Line.h"
#include "../stream/include/CodeStream.h"
#include "../stream/include/CodeReader.h"
#include "../stream/include/CodeWriter.h"
class pBuild {
private:
    BuildVal *bVals;
    CodeReader *reader;
    CodeWriter *out;
    bool ignore=false;
    bool def_ignre=false;
    b_stat block_sym_build(string *, unsigned int);

    b_stat invoke_line_build(string *lineP, unsigned int kStart);

    int is_invoke_line(string *lineP);

    static int *find_next_symbol(string *lineP, unsigned int kStart);

    bool has_symbol(const string *str);
    FuncInfo* define_function_build(string arg1,string arg2);
public:
    static int find_unmirr_char(const char *, const char, int);

    pBuild();

    pBuild(CodeReader *reader, CodeWriter *out);

    pBuild(CodeReader *reader, CodeWriter *out, BuildVal *bVals);

    ~pBuild();

    b_stat build(const char *line);

    b_stat build(char *line);

    b_stat build(char *line, CodeWriter *out);

    b_stat build(string line);

    b_stat build(Line *line);

    b_stat build();
};


#endif //CPPPREBUILD_PBUILD_H
