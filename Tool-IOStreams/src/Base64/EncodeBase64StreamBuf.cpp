/**
 * @file EncodeBase64StreamBuf.cpp
 *
 * @brief File for class EncodeBase64StreamBuf
 * @date 05.08.2016
 * @author duke
 */

#include <string.h>
#include "EncodeBase64StreamBuf.h"

EncodeBase64StreamBuf::EncodeBase64StreamBuf(ostream& a_out) :
        Base64StreamBuf(a_out)
{
    pc_outbuffer = new char[(c_bufsize + 3) * 4 / 3 + 1];

    setp(pc_inbuffer, pc_inbuffer + c_bufsize - 1);
}

EncodeBase64StreamBuf::~EncodeBase64StreamBuf()
{
    try
    {
        execute(true);
    }
    catch (exception &x)
    {
        cerr << x.what() << endl;
    }
    catch (...)
    {
    }

    delete[] pc_outbuffer;
}

int EncodeBase64StreamBuf::execute(bool a_final)
{
    try
    {
        size_t l_size = (pptr() - pbase());
        if (l_size == 0)
            return 0;

        // Only handle full 3 byte blocks if a_final is not set
        size_t l_overflow = (a_final ? 0 : (l_size % 3));
        size_t l_border = (a_final ? l_size : ((l_size / 3) * 3));

        size_t l_len = Base64encode(pc_outbuffer, pbase(), l_border);

        c_out.write(pc_outbuffer, l_len - 1);

        setp(pbase(), pbase() + c_bufsize - 1);

        // Copy the overflow to the beginning of the input buffer
        // And adjust the starting pointer
        if (l_overflow)
        {
            memcpy(pbase(), pbase() + l_border, l_overflow);
            pbump(l_overflow);
        }

        if (a_final)
            c_out.flush();

    }
    catch (...)
    {
        c_out.flush();

        setp(pc_inbuffer, pc_inbuffer + c_bufsize - 1);
        throw;
    }

    return 0;
}

