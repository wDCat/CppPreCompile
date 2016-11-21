cmake_minimum_required(VERSION 3.6)
project(CppPreBuild)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        util/helper.cpp util/include/helper.h util/exceptions.cpp util/include/exceptions.h stream/Line.cpp stream/include/Line.h util/dlog.cpp util/include/dlog.h stream/CodeStream.cpp stream/include/CodeStream.h stream/FileCodeStream.cpp stream/include/FileCodeStream.h stream/BlockCodeStream.cpp stream/include/BlockCodeStream.h stream/CodeReader.cpp stream/include/CodeReader.h pBuild.cpp include/pBuild.h struct/BuildVal.cpp struct/BuildVal.h stream/CodeWriter.cpp stream/include/CodeWriter.h util/G.cpp util/include/G.h stream/MemoryCodeWriter.cpp stream/include/MemoryCodeWriter.h stream/FileCodeWriter.cpp stream/include/FileCodeWriter.h)
add_executable(CppPreBuild ${SOURCE_FILES})