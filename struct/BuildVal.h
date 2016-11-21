//
// Created by whmwi on 2016/11/5.
//

#ifndef CPPPREBUILD_BUILDVAL_H
#define CPPPREBUILD_BUILDVAL_H

#include <iostream>
#include <cstdlib>
#include <map>
#include <list>

#define func_mark __func_mark

using namespace std;
extern string __func_mark;

struct FuncInfo {
    string methodName;
    list<string> args;
    string content;

    FuncInfo(const string &content);

    FuncInfo(const string &methodName, const string &content);
};

struct BuildVal {
    bool as_block=false;
    map<string, string> definedMap;
    map<string, FuncInfo *> funcMap;

    BuildVal();

    virtual ~BuildVal();
};


#endif //CPPPREBUILD_BUILDVAL_H
