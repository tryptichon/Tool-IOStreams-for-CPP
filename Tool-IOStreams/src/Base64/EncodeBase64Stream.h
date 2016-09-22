/**
 * @file EncodeBase64Stream.h
 *
 * @brief File for class EncodeBase64Stream
 * @date 05.08.2016
 * @author duke
 */

#ifndef SRC_ENCODEBASE64STREAM_H_
#define SRC_ENCODEBASE64STREAM_H_

#include "Base64Stream.h"

class EncodeBase64Stream : public Base64Stream
{
public:
    EncodeBase64Stream(ostream &a_out);
    virtual ~EncodeBase64Stream();
};

#endif /* SRC_ENCODEBASE64STREAM_H_ */
