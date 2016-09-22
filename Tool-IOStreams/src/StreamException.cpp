/**
 * @file StreamException.cpp
 *
 * @brief File for class StreamException
 * @date 03.08.2016
 * @author duke
 */

#include "StreamException.h"

StreamException::StreamException(const string &a_msg) :
        c_msg(a_msg)
{
}

StreamException::~StreamException() throw ()
{
}

const char* StreamException::what() const throw ()
{
    return c_msg.c_str();
}
