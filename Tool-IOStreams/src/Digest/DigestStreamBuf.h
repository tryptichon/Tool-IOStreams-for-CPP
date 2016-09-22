/**
 * @file DigestStreamBuf.h
 * @brief File for class DigestStreamBuf
 * @date 05.08.2016
 * @author duke
 */

#ifndef SRC_DIGESTSTREAMBUF_H_
#define SRC_DIGESTSTREAMBUF_H_

#include <string>
#include <iostream>
#include "StreamException.h"

#include "zlib.h"
#include <openssl/evp.h>

using namespace std;

class DigestStreamBuf: public streambuf
{
    ostream &c_out;

    static bool c_libInitialized;

    char *pc_buffer;
    const size_t c_bufsize;

    string c_digestName;

    size_t c_size;
    string c_digestResult;

    EVP_MD_CTX *pc_ctx;
    const EVP_MD *pc_md;

    int execute();

public:
    DigestStreamBuf(ostream &a_out, const string &a_digestName, size_t a_bufsize = 1024);
    virtual ~DigestStreamBuf();

    int overflow(int a_ch);
    int sync();

    virtual size_t size();
    virtual const string &digest();
};

#endif /* SRC_DIGESTSTREAMBUF_H_ */
