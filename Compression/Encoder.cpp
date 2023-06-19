// #include <fstream>
// #include <iomanip>
// #include <iostream>
// #include <math.h>
// #include <stdlib.h>
// #include <string>
// #include <vector>

#include <bits/stdc++.h>
#include "./Huffman.h"

using namespace std;

int main()
{
    string str = "dabeeababbebeaeadcccaaddcbbaccaaccaabccffbfbfbdg";
    
    cout << Huffman::EncodeString(str);

    return 0;
}

