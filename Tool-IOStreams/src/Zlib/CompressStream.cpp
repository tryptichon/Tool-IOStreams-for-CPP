/**
 * @file CompressStream.cpp
 *
 * @brief File for class CompressStream
 * @date 04.08.2016
 * @author duke
 */

#include "CompressStream.h"
#include "CompressStreamBuf.h"

CompressStream::CompressStream(ostream &a_out, int a_level) :
        ZlibStream(new CompressStreamBuf(a_out, a_level))
{
    exceptions(ios::badbit);
}

CompressStream::~CompressStream()
{
    delete rdbuf();
}

