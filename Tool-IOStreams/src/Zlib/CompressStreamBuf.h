/**
 * @file CompressStreamBuf.h
 *
 * @brief File for class CompressStreamBuf
 * @date 04.08.2016
 * @author duke
 */

#ifndef SRC_COMPRESSSTREAMBUF_H_
#define SRC_COMPRESSSTREAMBUF_H_

#include <string>
#include <iostream>
#include "ZlibStreamBuf.h"

using namespace std;

class CompressStreamBuf: public ZlibStreamBuf
{
    int execute(bool a_final);

    int c_level;

public:
    CompressStreamBuf(ostream &a_out, int a_level = Z_DEFAULT_COMPRESSION, size_t a_bufsize = 16 * 1024);
    virtual ~CompressStreamBuf();
};

#endif /* SRC_COMPRESSSTREAMBUF_H_ */
