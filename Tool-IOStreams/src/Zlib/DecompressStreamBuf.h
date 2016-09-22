/**
 * @file DecompressStreamBuf.h
 *
 * @brief File for class DecompressStreamBuf
 * @date 04.08.2016
 * @author duke
 */

#ifndef SRC_DECOMPRESSSTREAMBUF_H_
#define SRC_DECOMPRESSSTREAMBUF_H_

#include <string>
#include <iostream>
#include "ZlibStreamBuf.h"

using namespace std;

class DecompressStreamBuf: public ZlibStreamBuf
{
    int execute(bool a_final);

public:
    DecompressStreamBuf(ostream &a_out, size_t a_bufsize = 16 * 1024);
    virtual ~DecompressStreamBuf();

};

#endif /* SRC_DECOMPRESSSTREAMBUF_H_ */
