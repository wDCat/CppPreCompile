#include <iostream>
#include "util/include/exceptions.h"
#include "stream/include/CodeStream.h"
#include "stream/include/Line.h"
#include "stream/include/FileCodeStream.h"
#include "stream/include/CodeReader.h"
#include "include/pBuild.h"
#include "stream/include/MemoryCodeWriter.h"
#include "stream/include/FileCodeWriter.h"

using namespace std;

bool class_line_test() {
    Line *l = new Line("   DCat Neko;//Nyaaa");
    cout << l->removeNotes() << endl;
    cout << l->trim() << endl;

}

bool class_codeinputstream_test() {
    CodeStream *cis = new FileCodeStream("i://mmm.cpp");
    /*
    while (!cis->isEOF())
        cout << cis->read() << endl;*/
    delete cis;
}

bool class_codereader_test() {
    CodeStream *cis = new FileCodeStream("i://mmm.cpp");
    CodeReader *cr = new CodeReader(cis);
    while (!cr->isEOF()) {
        cout << *cr->nextLine() << endl;
    }
    delete cr;

}

bool class_build_test() {
    CodeReader*cr =new CodeReader(new FileCodeStream("i://mmm.cpp"));
    FileCodeWriter*fcw = new FileCodeWriter("i://ppp.cpp");
    pBuild*pb = new pBuild(cr, fcw);
    pb->build();
    fcw->flush();
    fcw->close();
    delete pb, fcw, cr;
}

int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;
    class_build_test();
    return 0;
}

