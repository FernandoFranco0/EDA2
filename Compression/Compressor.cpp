#include <bits/stdc++.h>
#include "./Headers/bit.h"
#include "./Headers/HuffmanFile.h"
#include "./Headers/HuffmanString.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string Path = "";

    if (argc == 2){
        Path = argv[1];   
    }

    HuffmanFile::Compress(Path);

    
    return 0;
}

