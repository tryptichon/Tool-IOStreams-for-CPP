/**
 * @file main.cpp
 *
 * @brief main()
 * @date 03.08.2016
 * @author duke
 */

#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "EncodeBase64Stream.h"
#include "DecodeBase64Stream.h"
#include "IconvStream.h"
#include "IconvStringStream.h"
#include "CompressStream.h"
#include "DecompressStream.h"
#include "DigestStream.h"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        locale::global(locale(""));

        if (argc == 1)
            return 0;

        string l_filename = argv[1];

        ifstream infile(l_filename.c_str(), ios::in | ios::binary);
        if (!infile)
            throw StreamException("Cannot open intfile");

        ofstream outfile((l_filename + ".gz").c_str(), ios::out | ios::binary);
        if (!outfile)
            throw StreamException("Cannot open outfile");

        ofstream outfile2((l_filename + ".base64").c_str(), ios::out | ios::binary);
        if (!outfile)
            throw StreamException("Cannot open outfile");

        string l_digest = "MD5";
        if (argc >= 3)
            l_digest = argv[2];

        IconvStringStream toUtf8("ISO8859-15", "UTF-8");
        IconvStream toIso(toUtf8, "UTF-8", "ISO8859-15");
        DigestStream digestOut(outfile, l_digest);
        CompressStream compressOut(digestOut);
        DecodeBase64Stream textOut(outfile2);
        EncodeBase64Stream base64Out(textOut);

        toIso << fixed << setprecision(4) << "Hellö Wörldß! Hellö Wörldß! Hellö Wörldß!Hellö Wörldß! @€" << 10232.234;
        toIso.flush();

        cout << "UTF-8 : " << toUtf8.str() << endl;

        cout << IconvStringStream("This is cool€!", "UTF-8", "ISO8859-15").str() << endl;

        stringstream dump;

        dump << infile.rdbuf();

        compressOut << dump.str();
        compressOut << dump.str();
        compressOut.close();

        base64Out << dump.str();
        base64Out.close();

        cout << "Compressed: " << compressOut.size() << " / CRC " << hex << compressOut.crc() << dec << endl;
        cout << l_digest << "-Digest: " << digestOut.digest() << endl;

        infile.close();
        outfile.close();

        infile.open((l_filename + ".gz").c_str(), ios::in | ios::binary);
        if (!infile)
            throw StreamException("Cannot open intfile 2");

        DecompressStream inflateOut(cout);

        inflateOut << infile.rdbuf();
        inflateOut.close();

        cout << "Uncompressed: " << inflateOut.size() << " / CRC " << hex << inflateOut.crc() << dec << endl;

        return 0;
    }
    catch (StreamException &x)
    {
        cerr << x.what() << endl;
    }

    return -1;
}

