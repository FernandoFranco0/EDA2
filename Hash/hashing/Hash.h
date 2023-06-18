// #include<bits/stdc++.h>
// #include "Hash.h"

// using namespace std;

class Hash
{
public:
  int *array;
  bool *IsEmpty;
  int Modulo;
  int Counter;

  Hash(int HashSize)
  {
    array = new int[HashSize];

    Modulo = HashSize;

    Counter = 0;

    IsEmpty = new bool[HashSize];
    for (int i = 0; i < HashSize; i++)
    {
      IsEmpty[i] = true;
    }
  }

  ~Hash(){
    free(array);
    free(IsEmpty);
  }

  void PrintTable()
  {
    for (int i = 0; i < Hash::Modulo; i++)
    {
      cout << i << ": ";
      if (Hash::IsEmpty[i])
        cout << endl;
      else
        cout << Hash::array[i] << endl;
    }
  }
};