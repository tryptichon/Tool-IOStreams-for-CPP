/**
 * @file DecodeBase64Stream.cpp
 *
 * @brief File for class DecodeBase64Stream
 * @date 05.08.2016
 * @author duke
 */

#include "DecodeBase64Stream.h"
#include "DecodeBase64StreamBuf.h"

DecodeBase64Stream::DecodeBase64Stream(ostream &a_out) :
        Base64Stream(new DecodeBase64StreamBuf(a_out))
{
    exceptions(ios::badbit);
}

DecodeBase64Stream::~DecodeBase64Stream()
{
    delete rdbuf();
}

