/**
 * @file DigestStream.cpp
 * @brief File for class DigestStream
 * @date 05.08.2016
 * @author duke
 */

#include "DigestStream.h"
#include "DigestStreamBuf.h"

using namespace std;

DigestStream::DigestStream(ostream &a_out, const string &a_digest) :
        ostream(new DigestStreamBuf(a_out, a_digest))
{
    exceptions(ios::badbit);
    pc_streambuf = dynamic_cast<DigestStreamBuf *>(rdbuf());
}

DigestStream::~DigestStream()
{
    delete rdbuf();
}

size_t DigestStream::size()
{
    return pc_streambuf->size();
}

string DigestStream::digest()
{
    return pc_streambuf->digest();
}
