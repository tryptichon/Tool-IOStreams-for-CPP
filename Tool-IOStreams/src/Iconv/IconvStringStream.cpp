/**
 * @file IconvStringStream.cpp
 *
 * @brief File for class IconvStringStream
 * @date 04.08.2016
 * @author duke
 */

#include "IconvStringStream.h"

using namespace std;

IconvStringStream::IconvStringStream(const string& a_from, const string& a_to) :
        IconvStream(c_str, a_from, a_to)
{
}

IconvStringStream::IconvStringStream(const string& a_input, const string& a_from, const string& a_to) :
        IconvStream(c_str, a_from, a_to)
{
    *this << a_input;
}

IconvStringStream::~IconvStringStream()
{
}

string IconvStringStream::str()
{
    flush();
    return c_str.str();
}

