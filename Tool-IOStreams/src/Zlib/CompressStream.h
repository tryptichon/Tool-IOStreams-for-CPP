/**
 * @file CompressStream.h
 *
 * @brief File for class CompressStream
 * @date 04.08.2016
 * @author duke
 */

#ifndef SRC_COMPRESSSTREAM_H_
#define SRC_COMPRESSSTREAM_H_

#include "ZlibStream.h"

using namespace std;

class CompressStream : public ZlibStream
{
public:
    CompressStream(ostream &a_out, int a_level = Z_DEFAULT_COMPRESSION);
    virtual ~CompressStream();
};

#endif /* SRC_COMPRESSSTREAM_H_ */
