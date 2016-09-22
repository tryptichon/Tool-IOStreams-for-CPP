/**
 * @file IconvStream.h
 *
 * @brief File for class IconvStream
 * @date 03.08.2016
 * @author duke
 */

#ifndef SRC_ICONVSTREAM_H_
#define SRC_ICONVSTREAM_H_

#include <string>
#include <iostream>
#include "StreamException.h"

using namespace std;

class IconvStream : public ostream
{
public:
    IconvStream(ostream &a_out, const string &a_from, const string &a_to);
    virtual ~IconvStream();
};


#endif /* SRC_ICONVSTREAM_H_ */
