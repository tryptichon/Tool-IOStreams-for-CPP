/**
 * @file IconvStream.cpp
 *
 * @brief File for class IconvStream
 * @date 03.08.2016
 * @author duke
 */

#include "IconvStream.h"
#include "IconvStreamBuf.h"

IconvStream::IconvStream(ostream &a_out, const string &a_from, const string &a_to) :
        ostream(new IconvStreamBuf(a_out, a_from, a_to))
{
    exceptions(ios_base::badbit);
}

IconvStream::~IconvStream()
{
    delete rdbuf();
}

