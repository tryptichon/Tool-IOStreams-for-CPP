/**
 * @file EncodeBase64StreamBuf.h
 *
 * @brief File for class EncodeBase64StreamBuf
 * @date 05.08.2016
 * @author duke
 */

#ifndef SRC_ENCODEBASE64STREAMBUF_H_
#define SRC_ENCODEBASE64STREAMBUF_H_

#include "Base64StreamBuf.h"

class EncodeBase64StreamBuf : public Base64StreamBuf
{
    char *pc_outbuffer;

    virtual int execute(bool a_final);

public:
    EncodeBase64StreamBuf(ostream &a_out);
    virtual ~EncodeBase64StreamBuf();
};

#endif /* SRC_ENCODEBASE64STREAMBUF_H_ */
