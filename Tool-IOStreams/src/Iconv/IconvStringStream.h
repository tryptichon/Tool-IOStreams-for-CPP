/**
 * @file IconvStringStream.h
 *
 * @brief File for class IconvStringStream
 * @date 04.08.2016
 * @author duke
 */

#ifndef SRC_ICONVSTRINGSTREAM_H_
#define SRC_ICONVSTRINGSTREAM_H_

#include <string>
#include <sstream>
#include "IconvStream.h"

using namespace std;

class IconvStringStream: public IconvStream
{
    stringstream c_str;

public:
    IconvStringStream(const string &a_from, const string &a_to);
    IconvStringStream(const string &a_input, const string &a_from, const string &a_to);
    virtual ~IconvStringStream();

    string str();
};

#endif /* SRC_ICONVSTRINGSTREAM_H_ */
