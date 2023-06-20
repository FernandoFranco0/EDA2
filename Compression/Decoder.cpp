#include <bits/stdc++.h>
#include "bit.h"
#include "HuffmanFile.h"
#include "HuffmanString.h"
using namespace std;



int main(int argc, char const *argv[])
{
    string str = "dabeeababbebeaeadcccaaddcbbaccaaccaabccffbfbfbdg";

    HuffmanFile::Compress("In.txt");


    HuffmanFile::Decompress("Compressed.afc");
    
    return 0;
}
