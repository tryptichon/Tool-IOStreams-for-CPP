/**
 * @file DigestStreamBuf.cpp
 * @brief File for class DigestStreamBuf
 * @date 05.08.2016
 * @author duke
 */

#include "DigestStreamBuf.h"

using namespace std;

bool DigestStreamBuf::c_libInitialized = false;

DigestStreamBuf::DigestStreamBuf(ostream &a_out, const string &a_digestName, size_t a_bufsize) :
        c_out(a_out), c_bufsize(a_bufsize), c_digestName(a_digestName), c_size(0)
{
    try
    {
        if (!c_libInitialized)
        {
            OpenSSL_add_all_digests();
            c_libInitialized = true;
        }

        pc_ctx = EVP_MD_CTX_create();
        if (!pc_ctx)
            throw StreamException("Cannot create EVP_MD_CTX");

        pc_md = EVP_get_digestbyname(c_digestName.c_str());
        if (!pc_md)
            throw StreamException("No digest " + c_digestName);

        if (EVP_DigestInit_ex(pc_ctx, pc_md, NULL) != 1)
            throw StreamException("Error in EVP_DigestInit_ex");

        pc_buffer = new char[c_bufsize];

        setp(pc_buffer, pc_buffer + c_bufsize - 1);
    }
    catch (...)
    {
        if (pc_ctx)
        {
            EVP_MD_CTX_destroy(pc_ctx);
            pc_ctx = NULL;
        }

        pc_md = NULL;

        throw;
    }
}

DigestStreamBuf::~DigestStreamBuf()
{
    try
    {
        execute();
        c_out.flush();

        if (pc_ctx)
            EVP_MD_CTX_destroy(pc_ctx);

        delete[] pc_buffer;
    }
    catch (exception &x)
    {
        cerr << x.what() << endl;
    }
    catch (...)
    {
    }
}

int DigestStreamBuf::execute()
{
    try
    {
        size_t l_size = (pptr() - pbase());
        if (l_size == 0)
            return 0;

        if (EVP_DigestUpdate(pc_ctx, pbase(), l_size) != 1)
            throw StreamException("Error in EVP_DigestUpdate");

        c_size += l_size;

        c_out.write(pbase(), l_size);

        setp(pc_buffer, pc_buffer + c_bufsize - 1);
    }
    catch (...)
    {
        c_out.flush();

        setp(pc_buffer, pc_buffer + c_bufsize - 1);
        throw;
    }

    return 0;
}

int DigestStreamBuf::overflow(int a_ch)
{
    if (c_out && a_ch != traits_type::eof())
    {
        *pptr() = char(a_ch);
        pbump(1);
        if (!execute())
            return a_ch;
    }

    return traits_type::eof();
}

int DigestStreamBuf::sync()
{
    if (execute())
        return -1;

    c_out.flush();
    return 0;
}

size_t DigestStreamBuf::size()
{
    return c_size;
}

const string &DigestStreamBuf::digest()
{
    unsigned char *digest = NULL;
    try
    {
        unsigned int digest_len = 0;
        unsigned char *digest = (unsigned char *) OPENSSL_malloc(EVP_MD_size(pc_md));
        if (!digest)
            throw StreamException("Error in OPENSSL_malloc");

        if (EVP_DigestFinal_ex(pc_ctx, digest, &digest_len) != 1)
            throw StreamException("Error in EVP_DigestFinal_ex");

        for (size_t i = 0; i < digest_len; ++i)
        {
            char buf[3];
            sprintf(buf, "%02x", digest[i]);
            c_digestResult.append(buf);
        }

        OPENSSL_free(digest);
    }
    catch (...)
    {
        if (digest)
            OPENSSL_free(digest);
        throw;
    }

    return c_digestResult;
}
