/**
 * @file CompressStreamBuf.cpp
 *
 * @brief File for class CompressStreamBuf
 * @date 04.08.2016
 * @author duke
 */

#include "CompressStreamBuf.h"

CompressStreamBuf::CompressStreamBuf(ostream &a_out, int a_level, size_t a_bufsize) :
        ZlibStreamBuf(a_out, a_bufsize), c_level(a_level)
{
    c_strm.zalloc = Z_NULL;
    c_strm.zfree = Z_NULL;
    c_strm.opaque = Z_NULL;
    int l_ret = deflateInit2(&c_strm, c_level, c_method, c_windowBits, c_memlevel, c_strategy);
    if (l_ret != Z_OK)
        throw StreamException("Compress: " + zerr(l_ret));
}

CompressStreamBuf::~CompressStreamBuf()
{
    try
    {
        execute(true);

        c_out.flush();
        deflateEnd(&c_strm);
    }
    catch (exception &x)
    {
        cerr << x.what() << endl;
    }
    catch (...)
    {
    }
}

int CompressStreamBuf::execute(bool a_final)
{
    try
    {
        int l_flush = (a_final ? Z_FINISH : Z_NO_FLUSH);
        int l_ret;

        c_strm.avail_in = pptr() - pbase();
        c_strm.next_in = reinterpret_cast<Bytef *>(pbase());

        do
        {
            c_strm.avail_out = c_bufsize;
            c_strm.next_out = reinterpret_cast<Bytef *>(pc_outbuffer);

            l_ret = deflate(&c_strm, l_flush);

            if (l_ret < 0)
                throw StreamException("Compress: " + zerr(l_ret));

            size_t l_outsize = c_bufsize - c_strm.avail_out;

            if (l_outsize)
            {
                c_out.write(pc_outbuffer, l_outsize);
                c_crc = crc32(c_crc, reinterpret_cast<Bytef *>(pc_outbuffer), l_outsize);
                c_size += l_outsize;
            }
        }
        while ((a_final && l_ret != Z_STREAM_END) || (a_final == false && c_strm.avail_out == 0));

        setp(pc_inbuffer, pc_inbuffer + c_bufsize - 1);
    }
    catch (...)
    {
        setp(pc_inbuffer, pc_inbuffer + c_bufsize - 1);
        throw;
    }

    return 0;
}

