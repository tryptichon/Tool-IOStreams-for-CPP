/**
 * @file IconvStreamBuf.h
 *
 * @brief File for class IconvStreamBuf
 * @date 03.08.2016
 * @author duke
 */

#ifndef SRC_ICONVSTREAMBUF_H_
#define SRC_ICONVSTREAMBUF_H_

#include <iconv.h>

#include <iostream>

using namespace std;

class IconvStreamBuf: public streambuf
{
    ostream &c_out;

    iconv_t c_ihandle;

    string c_from;
    string c_to;

    int iconvert();

    char *pc_inbuffer;
    char *pc_convbuffer;
    const size_t c_bufsize;

public:
    explicit IconvStreamBuf(ostream &a_out, const string &a_from, const string &a_to, size_t a_bufsize = 1024);
    virtual ~IconvStreamBuf();

    int overflow(int a_ch);
    int sync();

    const string& getFrom() const
    {
        return c_from;
    }

    const string& getTo() const
    {
        return c_to;
    }
};

#endif /* SRC_ICONVSTREAMBUF_H_ */
