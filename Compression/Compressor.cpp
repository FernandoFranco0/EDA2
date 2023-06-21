#include <bits/stdc++.h>
#include "./Headers/bit.h"
#include "./Headers/HuffmanFile.h"
#include "./Headers/HuffmanString.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string Path = "";
    int a;

    if(argc == 1){
        cout << "Passe o nome de um arquivo como primeiro parametro. Aperte algo para sair";
    }
    else if (argc >= 2){
        Path = argv[1];   
        HuffmanFile::Decompress(Path);
        cout << "Compressao terminada. Aperte algo para sair";
    }
    cin >> a;

    
    return 0;
}

