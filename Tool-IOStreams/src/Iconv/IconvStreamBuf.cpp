/**
 * @file IconvStreamBuf.cpp
 *
 * @brief File for class IconvStreamBuf
 * @date 03.08.2016
 * @author duke
 */

#include <errno.h>
#include <string.h>
#include "IconvStreamBuf.h"
#include "StreamException.h"

IconvStreamBuf::IconvStreamBuf(ostream &a_out, const string &a_from, const string &a_to, size_t a_bufsize) :
        c_out(a_out), c_from(a_from), c_to(a_to), c_bufsize(a_bufsize)
{
    if ((c_ihandle = iconv_open(a_to.c_str(), a_from.c_str())) == (iconv_t) -1)
    {
        if (errno == EINVAL)
            throw StreamException("Iconv: No conversion " + a_from + " -> " + a_to);
        else
            throw StreamException("Iconv: " + string(strerror(errno)));
    }

    pc_inbuffer = new char[c_bufsize];
    pc_convbuffer = new char[c_bufsize];

    setp(pc_inbuffer, pc_inbuffer + c_bufsize - 1);
}

IconvStreamBuf::~IconvStreamBuf()
{
    try
    {
        iconvert();
        c_out.flush();

        delete[] pc_inbuffer;
        delete[] pc_convbuffer;

        iconv_close(c_ihandle);
    }
    catch (exception &x)
    {
        cerr << x.what() << endl;
    }
    catch (...)
    {
    }
}

int IconvStreamBuf::iconvert()
{
    size_t l_srcsize = pptr() - pbase();
    if (l_srcsize == 0)
        return 0;

    // Reset the pointers
    // This has to be done before iconv because of a possible EINVAL below
    setp(pc_inbuffer, pc_inbuffer + c_bufsize - 1);

    size_t l_convsize = c_bufsize;
    char *p_src = pc_inbuffer;
    char *p_dest = pc_convbuffer;
    bool l_finished = false;

    while (!l_finished)
    {
        if ((iconv(c_ihandle, &p_src, &l_srcsize, &p_dest, &l_convsize)) == (size_t) -1)
        {
            switch (errno)
            {
                case EILSEQ:
                    // The encountered bytes cannot be converted
                    throw StreamException("Iconv: " + string(strerror(errno)));

                case EINVAL:
                    // We are stuck between a multibyte character and need more data
                    // Write what was successfully converted, then shove the remaining bytes
                    // to the start of pc_inbuffer and set the starting pointer next to them
                    c_out.write(pc_convbuffer, p_dest - pc_convbuffer);

                    memcpy(pc_inbuffer, p_src, l_srcsize);
                    pbump(l_srcsize);
                    l_finished = true;

                    break;

                case E2BIG:
                    // The output buffer cannot hold all the data...
                    // Write what we have, then set the destination pointer to the beginning of pc_convbuffer again
                    // to resume converting the rest of the bytes in p_src
                    c_out.write(pc_convbuffer, p_dest - pc_convbuffer);

                    p_dest = pc_convbuffer;
                    l_convsize = c_bufsize;

                    break;

                default:
                    // Some unknown error
                    throw StreamException("Iconv: " + string(strerror(errno)));
            }
        }
        else
        {
            // Everything successfully converted
            c_out.write(pc_convbuffer, p_dest - pc_convbuffer);
            l_finished = true;
        }
    }

    return 0;
}

int IconvStreamBuf::overflow(int a_ch)
{
    if (c_out && a_ch != traits_type::eof())
    {
        *pptr() = char(a_ch);
        pbump(1);
        if (!iconvert())
            return a_ch;
    }

    return traits_type::eof();
}

int IconvStreamBuf::sync()
{
    if (iconvert())
        return -1;

    c_out.flush();
    return 0;
}
