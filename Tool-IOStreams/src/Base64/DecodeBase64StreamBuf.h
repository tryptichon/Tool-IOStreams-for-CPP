/**
 * @file DecodeBase64StreamBuf.h
 *
 * @brief File for class DecodeBase64StreamBuf
 * @date 05.08.2016
 * @author duke
 */

#ifndef SRC_DECODEBASE64STREAMBUF_H_
#define SRC_DECODEBASE64STREAMBUF_H_

#include "Base64StreamBuf.h"

class DecodeBase64StreamBuf : public Base64StreamBuf
{
    char *pc_outbuffer;

    virtual int execute(bool a_final);

public:
    DecodeBase64StreamBuf(ostream &a_out);
    virtual ~DecodeBase64StreamBuf();
};

#endif /* SRC_DECODEBASE64STREAMBUF_H_ */
