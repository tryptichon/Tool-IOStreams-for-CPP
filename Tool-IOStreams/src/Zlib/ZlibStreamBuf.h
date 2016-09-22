/**
 * @file ZlibStreamBuf.h
 *
 * @brief File for class ZlibStreamBuf
 * @date 04.08.2016
 * @author duke
 */

#ifndef SRC_ZLIBSTREAMBUF_H_
#define SRC_ZLIBSTREAMBUF_H_

#include <string>
#include <iostream>
#include "StreamException.h"

#include "zlib.h"

using namespace std;

class ZlibStreamBuf: public streambuf
{
protected:
    const static int c_method = Z_DEFLATED;
    const static int c_windowBits = 31; // 15 + 16 for gzip compatibility
    const static int c_memlevel = 8;
    const static int c_strategy = Z_DEFAULT_STRATEGY;

    z_stream c_strm;
    ostream &c_out;

    char *pc_inbuffer;
    char *pc_outbuffer;
    const size_t c_bufsize;

    size_t c_size, c_finalSize;
    uLong c_crc, c_finalCrc;

    virtual string zerr(int a_code);

    virtual int execute(bool a_final) = 0;

    ZlibStreamBuf(ostream &a_out, size_t a_bufsize = 16 * 1024);

public:
    virtual ~ZlibStreamBuf();

    virtual int overflow(int a_ch);
    virtual int sync();

    virtual void close();
    virtual size_t size();
    virtual uLong crc();
};

#endif /* SRC_ZLIBSTREAMBUF_H_ */
