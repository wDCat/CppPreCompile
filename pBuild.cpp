//
// Created by whmwi on 2016/11/3.
//

#include <cstring>
#include "include/pBuild.h"
#include "util/include/dlog.h"
#include "stream/include/CodeReader.h"
#include "util/include/G.h"
#include "util/include/exceptions.h"
#include "stream/include/MemoryCodeWriter.h"
#include "stream/include/BlockCodeStream.h"

b_stat pBuild::build(Line *line     ) {
    //dlog << "at line:" << line->getText() << endl;
    //line->trim();
    //line->removeNotes();
    //dlog << "after trim:" << line->getText() << endl;
    return build(line->getText());
}

b_stat pBuild::build(const char *line) {
    char *p = new char[BUFF_SIZE];
    sprintf(p, "%s", line);
    build(p);
    delete[] p;
}

b_stat pBuild::build(string line) {
    return build(const_cast<char *>(line.c_str()));
}

b_stat pBuild::build() {
    b_stat ret = 0;
    dlog << "-------------------------------------" << endl;
    while (!reader->isEOF()) {
        Line *line = reader->nextLine();
        ret = build(line);
        if (ret == BUILD_ERR) {
            derr << "error happened during building line:" << line->getText() << endl;
            break;
        }
        if (ret == BUILD_DONE && !bVals->as_block)
            out->write(";\n");
        delete line;
    }
    if (ret == BUILD_ERR)
        dlog << "error" << endl;
    else
        dlog << "read eof" << endl;
    dlog << "-------------------------------------" << endl;
    return ret;

}

int pBuild::find_unmirr_char(const char *line, const char c, int start) {
    int *mirr_sym_count = new int[G.mirror_sym_length];
    for (unsigned int x = 0; x < G.mirror_sym_length; x++)mirr_sym_count[x] = 0;//初始化
    for (int x = start; x < strlen(line); x++) {
        char nc = line[x];
        for (int y = 0; y < G.mirror_sym_length; y++) {

            if (nc == c) {
                bool isfound = true;
                for (int p = 0; p < G.mirror_sym_length; p++) {
                    if (mirr_sym_count[p] != 0) {
                        isfound = false;
                        break;
                    }//在范围内
                }
                if (isfound) {
                    delete[] mirr_sym_count;
                    return x;
                }
            }
            if (G.mirror_sym[y][0] == G.mirror_sym[y][1] && nc == G.mirror_sym[y][0]) {
                mirr_sym_count[y] = (mirr_sym_count[y] == 0) ? 1 : 0;
            } else if (nc == G.mirror_sym[y][0]) {
                mirr_sym_count[y]++;
            } else if (nc == G.mirror_sym[y][1]) {
                mirr_sym_count[y]--;
            }
        }
    }
    delete[] mirr_sym_count;
    return -1;//没有找到
}

pBuild::pBuild() {
    bVals = new BuildVal;
}

pBuild::pBuild(CodeReader *reader, CodeWriter *out) : reader(reader), out(out) {
    bVals = new BuildVal;
}

pBuild::pBuild(CodeReader *reader, CodeWriter *out, BuildVal *bVals) : reader(reader), out(out), bVals(bVals) {

}

pBuild::~pBuild() {
    delete bVals;
    if (out != nullptr)
        delete out;
}

bool pBuild::has_symbol(const string *str) {
    for (int x = 0; x < G.symbol_length; x++) {
        int k = (unsigned) str->find(G.symbols[x], 0);
        if (k >= 0) {
            dlog << "found:" << G.symbols[x] << endl;
            return true;
        }
    }
    return false;
}

b_stat pBuild::block_sym_build(string *lineP, unsigned int bStart) {
    Line *nLine = new Line(lineP->c_str());
    dlog << "block expr:" << lineP->substr(0, bStart) << endl;
    /*
    CodeReader *blockReader = new CodeReader(reader->nextBlock(nLine));
    (new pBuild(blockReader, out, bVals))->build();*/

}

int pBuild::is_invoke_line(string *lineP) {
    int kStart = find_unmirr_char(lineP->c_str(), '(', 0);
    int kEnd = find_unmirr_char(lineP->c_str(), ')', kStart);
    string mName = lineP->substr(0, kStart - 1);
    if (has_symbol(&mName))return 0;
    dlog << "kstart  " << kStart << "   kEnd:" << kEnd << endl;
    if (kStart == -1 || kEnd == -1)return 0;
    return kStart;
}

b_stat pBuild::invoke_line_build(string *lineP, unsigned int kStart) {
    string methodName = lineP->substr(0, kStart);
    bool isDefinedMethod = false, __not_ignore = false;
    map<string, string> argMap;
    list<string> __temp_list;
    _List_iterator<string> argIter = __temp_list.begin();
    dlog << "methodName:[" << methodName << "]" << endl;
    if (bVals->funcMap.count(methodName) > 0) {
        dlog << "defined method:" << methodName << endl;
        isDefinedMethod = true;
        argIter = bVals->funcMap[methodName]->args.begin();
    }
    if (!isDefinedMethod) {
        build(methodName);
        out->write("(");
    }
    int kEnd = find_unmirr_char(lineP->c_str(), ')', kStart);
    int lIndex = kStart;
    while (lIndex < kEnd) {
        if (!isDefinedMethod && kStart != lIndex)
            out->write(",");
        int nS = find_unmirr_char(lineP->c_str(), ',', lIndex + 1);
        //dlog << "ns:" << nS << endl;
        string arg;
        if (nS == -1) {
            arg = lineP->substr((unsigned) lIndex + 1, (unsigned) kEnd - (lIndex + 1));
            lIndex = kEnd;
        } else {
            arg = lineP->substr((unsigned) lIndex + 1, (unsigned) nS - (lIndex + 1));
            lIndex = nS;
        }
        dlog << "arg:[" + arg << "]" << endl;
        if (!isDefinedMethod)
            build(arg);
        else {
            dlog << "value map [" << *argIter << "] to [" << arg << "]" << endl;
            *argIter = Line::trim((*argIter).c_str());
            arg = Line::trim(arg.c_str());
            argMap[*argIter] = arg;
            argIter++;
        }
    }
    if (!isDefinedMethod)
        out->write(")");
    else {
        CodeStream *funcCS = new BlockCodeStream(bVals->funcMap[methodName]->content.c_str());
        CodeReader *funcReader = new CodeReader(funcCS);
        BuildVal *bv = new BuildVal();
        for (auto iter = bVals->funcMap[methodName]->args.begin();
             iter != bVals->funcMap[methodName]->args.end(); iter++) {
            bv->definedMap[*iter] = argMap[*iter];
        }
        bv->as_block = true;
        MemoryCodeWriter *funcCW = new MemoryCodeWriter(BUFF_SIZE * 2);
        pBuild *builder = new pBuild(funcReader, funcCW, bv);
        dlog << "building block...." << endl;
        builder->build();
        dlog << "built." << endl;
        funcCW->toFileCodeWriter(out);
    }
    return BUILD_DONE;
}

FuncInfo *pBuild::define_function_build(string arg1, string arg2) {
    int kStart = is_invoke_line(&arg1);
    if (!kStart)return nullptr;
    string methodName = arg1.substr(0, kStart);
    FuncInfo *funcInfo = new FuncInfo(methodName, arg2);
    dlog << "defined func name:[" << methodName << "]" << endl;
    int kEnd = find_unmirr_char(arg1.c_str(), ')', kStart);
    int lIndex = kStart;
    while (lIndex < kEnd) {
        int nS = find_unmirr_char(arg1.c_str(), ',', lIndex + 1);
        string arg;
        if (nS == -1) {
            arg = arg1.substr((unsigned) lIndex + 1, (unsigned) kEnd - (lIndex + 1));
            lIndex = kEnd;
        } else {
            arg = arg1.substr((unsigned) lIndex + 1, (unsigned) nS - (lIndex + 1));
            lIndex = nS;
        }
        dlog << "defined func arg:[" + arg << "]" << endl;
        funcInfo->args.push_back(arg);
    }
    return funcInfo;
}

int *pBuild::find_next_symbol(string *lineP, unsigned int kStart) {
    for (int p = 0; p < G.symbol_length; p++) {
        int k = (int) lineP->find(G.symbols[p], kStart);
        if (k >= 0) {
            //dlog << "found at" << lineP->find(G.symbols[p], kStart) << endl;
            return new int[2]{p, k};
        }
    }
    return 0;
}

b_stat pBuild::build(char *line) {
    //handle
    /*
    MemoryCodeWriter *mcw = new MemoryCodeWriter((int) strlen(line) * 2);
    int ret = build(line, mcw);
    mcw->toFileCodeWriter(this->out);
    this->out->write(";\n");
    return ret;*/
    return build(line, this->out);
}

b_stat pBuild::build(char *line, CodeWriter *out) {
#define IGNORE_CHECK if (def_ignre) {\
    dlog << "ignore line:" << lineP << endl;\
    return BUILD_IGNORE;\
}
#define ARG_REQUEST(__x__) if (__x__==1&&arg1 == null_string) \
    throw BuildException("missing arg. 1", line);\
else if(__x__==2&&arg2 == null_string)\
throw BuildException("missing arg. 2", line);

    dlog << "atLine: [" << line << "]" << endl;
    if (Line::removeNotes(line, ignore)) {
        dlog << "ignore line:" << line << endl;
        return BUILD_IGNORE;
    }
    line = Line::trim(line);
    dlog << "trimed:[" << line << "]" << endl;
    string *lineP = new string(line);
    if (lineP->length() == 0) {
        dlog << "empty line" << endl;
        return BUILD_IGNORE;
    }
    if (lineP->at(0) == '#') {//预编译行
        int sp1 = find_unmirr_char(line, ' ', 0);
        int sp2 = find_unmirr_char(line, ' ', sp1 + 1);
        string cmd = lineP->substr(0, sp1);
        string arg1 = null_string, arg2 = null_string;
        if (sp2 > 0)
            arg2 = lineP->substr((unsigned) sp2 + 1);
        else if (sp2 == -1)sp2 = (int) strlen(line);
        if (sp1 > 0)
            arg1 = lineP->substr((unsigned) sp1 + 1, (unsigned) sp2 - sp1 - 1);
        dlog << sp1 << " " << sp2 << endl;
        dlog << "cmd:[" << cmd << "] arg1[" << arg1 << "] arg2[" << arg2 << "]" << endl;
        if (cmd == "#include") {
            IGNORE_CHECK;
            //Ignored.
            //cmd = "//include from '" + arg1 + "' ignored.\n";
            //out->write(cmd);
        } else if (cmd == "#define") {
            IGNORE_CHECK;
            ARG_REQUEST(1);
            if (arg2 == null_string) {
                arg2 = "";
            }
            dlog << "define [" << arg1 << "] to [" << arg2 << "]" << endl;
            FuncInfo *funcInfo = define_function_build(arg1, arg2);
            if (funcInfo != nullptr) {//define函数
                bVals->definedMap[funcInfo->methodName] = func_mark;
                bVals->funcMap[funcInfo->methodName] = funcInfo;
            } else {
                bVals->definedMap[arg1] = arg2;
            }
        } else if (cmd == "#ifdef") {
            IGNORE_CHECK;
            ARG_REQUEST(1);
            if (bVals->definedMap.count(arg1) == 0) {
                dlog << "ifdef " << arg1 << " false" << endl;
                def_ignre = true;
            }
        } else if (cmd == "#ifndef") {
            IGNORE_CHECK;
            ARG_REQUEST(1);
            if (bVals->definedMap.count(arg1) > 0) {
                dlog << "ifndef " << arg1 << " false" << endl;
                def_ignre = true;
            }
        } else if (cmd == "#endif") {
            def_ignre = false;
        } else if (cmd == "#else") {
            def_ignre = !def_ignre;
        } else if (cmd == "#undef") {
            IGNORE_CHECK;
            ARG_REQUEST(1);
            bVals->definedMap.erase(arg1);
        } else if (cmd == "#error") {
            IGNORE_CHECK;
            derr << "Error:" << arg1 << "  " << arg2 << endl;
            return BUILD_ERR;
        }
        return BUILD_IGNORE;
    }
    if (def_ignre) {
        dlog << "ignore line:" << lineP << endl;
        return BUILD_IGNORE;
    }

    int blockStartSym = find_unmirr_char(line, '{', 0);
    if (blockStartSym != -1) //块
    {

        build(lineP->substr(0, (unsigned) blockStartSym));
        out->write("{\n");
        return build(lineP->substr((unsigned) blockStartSym + 1));
    }

    int blockEndSym = find_unmirr_char(line, '}', 0);
    if (blockEndSym != -1) //块
    {

        build(lineP->substr(0, (unsigned) blockEndSym));
        out->write("}\n");
        return build(lineP->substr((unsigned) blockEndSym + 1));
    }

    int eqSym = find_unmirr_char(line, '=', 0);
    if (eqSym != -1) {
        //赋值表达式
        string sTo = lineP->substr(0, (unsigned) eqSym);
        string sFrom = lineP->substr((unsigned) eqSym + 1);
        dlog << "set to[" << sTo << "] from [" + sFrom << "]" << endl;
        build(sTo);
        out->write("=");
        build(sFrom);
        return BUILD_DONE;
    }
    int mhSym = find_unmirr_char(line, ':', 0);
    if (mhSym != -1 && mhSym == lineP->length() - 1) {
        //赋值表达式
        string sTo = lineP->substr(0, (unsigned) mhSym);
        build(sTo);
        out->write(":");
        return BUILD_IGNORE;
    }
    int invokeSym = is_invoke_line(lineP);
    if (invokeSym > 0) {
        return invoke_line_build(lineP, (unsigned) invokeSym);
    }
    if (!has_symbol(lineP)) {
        dlog << "no symbol.." << endl;
        int p = find_unmirr_char(line, ' ', 0);
        if (p > 0) {
            //含空格表达式
            string part1 = lineP->substr(0, (unsigned) p);
            string part2 = lineP->substr((unsigned) p + 1);
            dlog << "[]kg expr part1:[" + part1 << "] part2:[" << part2 << "]" << endl;
            build(part1);
            out->write(" ");
            build(part2);
            return BUILD_DONE;
        } else {
            //数据
            dlog << "data[" << *lineP << "]" << endl;
            if (bVals->definedMap.count(*lineP) > 0) {
                const string val = bVals->definedMap[*lineP];
                dlog << "replace [" << *lineP << "] to [" << val << "]" << endl;
                out->write(val);
            } else
                out->write(lineP);
            return BUILD_DONE;
        }
    } else {
        int *result = find_next_symbol(lineP, 0);
        if (result) {
            dlog << "found symbol:"
                 << G.symbols[result[0]]
                 << "  at:" << result[1]
                 << endl;
            string r1, r2;
            r1 = lineP->substr(0, (unsigned) result[1]);
            r2 = lineP->substr(result[1] + strlen(G.symbols[result[0]]));
            dlog << "split symbol [" << r1 << "] and [" << r2 << "]" << endl;
            build(r1);
            out->write(G.symbols[result[0]]);
            build(r2);
            delete[] result;
            return BUILD_DONE;
        } else {
            derr << "[INNER ERROR]no symbol found for [" << line << "]" << endl;
            return BUILD_ERR;
        }
    }
    derr << "no handle found for [" << line << "]" << endl;
    return BUILD_ERR;
#undef IGNORE_CHECK
#undef ARG_REQUEST
}




