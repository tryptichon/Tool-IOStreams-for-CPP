/**
 * @file DecompressStream.h
 *
 * @brief File for class DecompressStream
 * @date 04.08.2016
 * @author duke
 */

#ifndef SRC_DECOMPRESSSTREAM_H_
#define SRC_DECOMPRESSSTREAM_H_

#include "ZlibStream.h"

using namespace std;

class DecompressStream: public ZlibStream
{
public:
    DecompressStream(ostream &a_out);
    virtual ~DecompressStream();
};

#endif /* SRC_DECOMPRESSSTREAM_H_ */
