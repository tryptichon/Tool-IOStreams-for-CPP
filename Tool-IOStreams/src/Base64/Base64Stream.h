/**
 * @file Base64Stream.h
 *
 * @brief File for class Base64Stream
 * @date 05.08.2016
 * @author duke
 */

#ifndef SRC_BASE64STREAM_H_
#define SRC_BASE64STREAM_H_

#include "Base64StreamBuf.h"

using namespace std;

class Base64Stream : public ostream
{
    Base64StreamBuf *pc_streambuf;

public:
    Base64Stream(Base64StreamBuf *pa_streambuf);
    virtual ~Base64Stream();

    virtual void close();
};

#endif /* SRC_BASE64STREAM_H_ */
