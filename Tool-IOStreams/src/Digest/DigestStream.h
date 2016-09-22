/**
 * @file DigestStream.h
 * @brief File for class DigestStream
 * @date 05.08.2016
 * @author duke
 */

#ifndef SRC_DIGESTSTREAM_H_
#define SRC_DIGESTSTREAM_H_

#include <string>
#include "DigestStreamBuf.h"

using namespace std;

class DigestStream: public ostream
{
    DigestStreamBuf *pc_streambuf;

public:
    DigestStream(ostream &a_out, const string &a_digest = "MD5");
    virtual ~DigestStream();

    virtual size_t size();
    virtual string digest();
};

#endif /* SRC_DIGESTSTREAM_H_ */
