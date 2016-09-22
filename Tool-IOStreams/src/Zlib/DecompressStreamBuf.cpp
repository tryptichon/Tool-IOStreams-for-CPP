/**
 * @file DecompressStreamBuf.cpp
 *
 * @brief File for class DecompressStreamBuf
 * @date 04.08.2016
 * @author duke
 */

#include "DecompressStreamBuf.h"

DecompressStreamBuf::DecompressStreamBuf(ostream &a_out, size_t a_bufsize) :
        ZlibStreamBuf(a_out, a_bufsize)
{
    c_strm.zalloc = Z_NULL;
    c_strm.zfree = Z_NULL;
    c_strm.opaque = Z_NULL;
    c_strm.avail_in = 0;
    c_strm.next_in = Z_NULL;
    int l_ret = inflateInit2(&c_strm, c_windowBits);
    if (l_ret != Z_OK)
        throw StreamException("Decompress: " + zerr(l_ret));
}

DecompressStreamBuf::~DecompressStreamBuf()
{
    try
    {
        execute(true);

        c_out.flush();
        inflateEnd(&c_strm);
    }
    catch (exception &x)
    {
        cerr << x.what() << endl;
    }
    catch (...)
    {
    }
}

int DecompressStreamBuf::execute(bool a_final)
{
    int l_ret;
    try
    {
        c_strm.avail_in = pptr() - pbase();
        c_strm.next_in = reinterpret_cast<Bytef *>(pbase());

        do
        {
            c_strm.avail_out = c_bufsize;
            c_strm.next_out = reinterpret_cast<Bytef *>(pc_outbuffer);

            l_ret = inflate(&c_strm, Z_NO_FLUSH);

            if (l_ret < 0 || l_ret == Z_NEED_DICT)
                throw StreamException("Decompress: " + zerr(l_ret));

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

