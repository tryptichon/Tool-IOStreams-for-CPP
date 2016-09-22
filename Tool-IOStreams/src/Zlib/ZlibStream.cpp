/**
 * @file ZlibStream.cpp
 *
 * @brief File for class ZlibStream
 * @date 04.08.2016
 * @author duke
 */

#include "ZlibStream.h"
#include "ZlibStreamBuf.h"

ZlibStream::ZlibStream(ZlibStreamBuf *pa_streambuf) :
        ostream(pa_streambuf), pc_streambuf(pa_streambuf)
{
}

ZlibStream::~ZlibStream()
{
}

size_t ZlibStream::size()
{
    return pc_streambuf->size();
}

uLong ZlibStream::crc()
{
    return pc_streambuf->crc();
}

void ZlibStream::close()
{
    pc_streambuf->close();
    clear();
}
