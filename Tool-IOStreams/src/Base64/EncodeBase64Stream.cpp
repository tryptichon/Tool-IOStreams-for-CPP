/**
 * @file EncodeBase64Stream.cpp
 *
 * @brief File for class EncodeBase64Stream
 * @date 05.08.2016
 * @author duke
 */

#include "EncodeBase64Stream.h"
#include "EncodeBase64StreamBuf.h"

EncodeBase64Stream::EncodeBase64Stream(ostream &a_out) :
        Base64Stream(new EncodeBase64StreamBuf(a_out))
{
    exceptions(ios::badbit);

}

EncodeBase64Stream::~EncodeBase64Stream()
{
    delete rdbuf();
}

