/**
 * @file DecompressStream.cpp
 *
 * @brief File for class DecompressStream
 * @date 04.08.2016
 * @author duke
 */

#include "DecompressStream.h"
#include "DecompressStreamBuf.h"

DecompressStream::DecompressStream(ostream &a_out) :
        ZlibStream(new DecompressStreamBuf(a_out))
{
    exceptions(ios::badbit);
}

DecompressStream::~DecompressStream()
{
    delete rdbuf();
}
