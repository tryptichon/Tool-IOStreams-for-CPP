/**
 * @file DecodeBase64Stream.h
 *
 * @brief File for class DecodeBase64Stream
 * @date 05.08.2016
 * @author duke
 */

#ifndef SRC_DECODEBASE64STREAM_H_
#define SRC_DECODEBASE64STREAM_H_

#include "Base64Stream.h"

class DecodeBase64Stream : public Base64Stream
{
public:
    DecodeBase64Stream(ostream &a_out);
    virtual ~DecodeBase64Stream();
};

#endif /* SRC_DECODEBASE64STREAM_H_ */
