#include <bits/stdc++.h>
#include "Huffman.h"
using namespace std;



int main(int argc, char const *argv[])
{
    string str = "dabeeababbebeaeadcccaaddcbbaccaaccaabccffbfbfbdg";

    auto a = Huffman::EncodeString(str);
    cout << a << endl;

    auto b = Huffman::DecodeString(a);
    cout << b << endl;
    return 0;
}
