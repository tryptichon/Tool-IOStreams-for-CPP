/**
 * @file ZlibStream.h
 *
 * @brief File for class ZlibStream
 * @date 04.08.2016
 * @author duke
 */

#ifndef SRC_ZLIBSTREAM_H_
#define SRC_ZLIBSTREAM_H_

#include "ZlibStreamBuf.h"

using namespace std;

class ZlibStream : public ostream
{
    ZlibStreamBuf *pc_streambuf;
public:
    ZlibStream(ZlibStreamBuf *pa_streambuf);
    virtual ~ZlibStream();

    virtual void close();
    virtual size_t size();
    virtual uLong crc();
};

#endif /* SRC_ZLIBSTREAM_H_ */
