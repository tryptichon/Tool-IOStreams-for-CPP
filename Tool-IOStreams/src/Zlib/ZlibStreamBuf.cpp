/**
 * @file ZlibStreamBuf.cpp
 *
 * @brief File for class ZlibStreamBuf
 * @date 04.08.2016
 * @author duke
 */

#include "ZlibStreamBuf.h"

using namespace std;

ZlibStreamBuf::ZlibStreamBuf(ostream& a_out, size_t a_bufsize) :
        c_out(a_out), c_bufsize(a_bufsize), c_size(0), c_finalSize(0), c_crc(0), c_finalCrc(0)
{
    pc_inbuffer = new char[c_bufsize];
    pc_outbuffer = new char[c_bufsize];

    setp(pc_inbuffer, pc_inbuffer + c_bufsize - 1);
}

ZlibStreamBuf::~ZlibStreamBuf()
{
    delete[] pc_inbuffer;
    delete[] pc_outbuffer;
}

string ZlibStreamBuf::zerr(int a_code)
{
    return zError(a_code);
}

int ZlibStreamBuf::overflow(int a_ch)
{
    if (c_out && a_ch != traits_type::eof())
    {
        *pptr() = char(a_ch);
        pbump(1);
        if (!execute(false))
            return a_ch;
    }

    return traits_type::eof();
}

int ZlibStreamBuf::sync()
{
    if (execute(false))
        return -1;

    return 0;
}

size_t ZlibStreamBuf::size()
{
    return c_finalSize;
}

void ZlibStreamBuf::close()
{
    execute(true);
    c_out.flush();

    c_finalSize = c_size;
    c_finalCrc = c_crc;
    c_size = 0;
    c_crc = 0;
}

uLong ZlibStreamBuf::crc()
{
    return c_finalCrc;
}
