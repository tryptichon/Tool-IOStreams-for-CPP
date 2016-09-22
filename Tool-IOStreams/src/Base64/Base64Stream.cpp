/**
 * @file Base64Stream.cpp
 *
 * @brief File for class Base64Stream
 * @date 05.08.2016
 * @author duke
 */

#include "Base64Stream.h"

Base64Stream::Base64Stream(Base64StreamBuf* pa_streambuf) :
        ostream(pa_streambuf), pc_streambuf(pa_streambuf)
{
}

Base64Stream::~Base64Stream()
{
}

void Base64Stream::close()
{
    pc_streambuf->close();
    clear();
}
