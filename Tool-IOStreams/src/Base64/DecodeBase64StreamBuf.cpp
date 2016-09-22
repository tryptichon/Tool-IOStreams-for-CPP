/**
 * @file DecodeBase64StreamBuf.cpp
 *
 * @brief File for class DecodeBase64StreamBuf
 * @date 05.08.2016
 * @author duke
 */

#include <string.h>
#include "DecodeBase64StreamBuf.h"

DecodeBase64StreamBuf::DecodeBase64StreamBuf(ostream &a_out) :
        Base64StreamBuf(a_out)
{
    pc_outbuffer = new char[(c_bufsize + 2) * 3 / 4 + 1];

    setp(pc_inbuffer, pc_inbuffer + c_bufsize - 1);
}

DecodeBase64StreamBuf::~DecodeBase64StreamBuf()
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

int DecodeBase64StreamBuf::execute(bool a_final)
{
    try
    {
        size_t l_size = (pptr() - pbase());
        if (l_size == 0)
            return 0;

        // Only handle full 4 byte blocks if a_final is not set
        size_t l_overflow = (a_final ? 0 : (l_size % 4));
        size_t l_border = (a_final ? l_size : ((l_size / 4) * 4));

        size_t l_len = Base64decode(pc_outbuffer, pbase(), l_border);

        c_out.write(pc_outbuffer, l_len);

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
