/**
 * @file StreamException.h
 *
 * @brief File for class StreamException
 * @date 03.08.2016
 * @author duke
 */

#ifndef SRC_STREAMEXCEPTION_H_
#define SRC_STREAMEXCEPTION_H_

#include <string>
#include <exception>

using namespace std;

class StreamException: public exception
{
    string c_msg;
public:
    StreamException(const string &a_msg);
    virtual ~StreamException() throw ();

    virtual const char *what() const throw ();
};

#endif /* SRC_STREAMEXCEPTION_H_ */
