//
// Created by whmwi on 2016/11/5.
//

#include "BuildVal.h"

BuildVal::BuildVal() {
}

BuildVal::~BuildVal() {
    //TODO: delete FuncInfo
}

FuncInfo::FuncInfo(const string &content) : content(content) {
}

FuncInfo::FuncInfo(const string &methodName, const string &content) : methodName(methodName), content(content) {}

string __func_mark("just a function");