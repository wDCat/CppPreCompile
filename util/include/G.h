//
// Created by whmwi on 2016/11/5.
//

#ifndef CPPPREBUILD_G_H
#define CPPPREBUILD_G_H

#include <string>

#define null_string empty_string

struct G_Static {
    static const int symbol_length = 20;
    const char *symbols[symbol_length] = {">>", "<<", "::", "[", "]", "==", "=", ",", "&", "**", "*", "<",
                                          ">", "?", "+", "-", "*", "/", "\\", ":"};
    static const int mirror_sym_length = 4;
    const char mirror_sym[mirror_sym_length][2] = {
            {'{',  '}'},
            {'(',  ')'},
            {'\"', '\"'},
            {'\'', '\''}
    };

};
extern G_Static G;
extern std::string empty_string;
#endif //CPPPREBUILD_G_H
