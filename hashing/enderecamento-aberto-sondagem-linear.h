// #include<bits/stdc++.h>
// #include "Hash.h"
// using namespace std;

class SondagemLinear : public Hash
{
public:
  SondagemLinear(int HashSize) : Hash(HashSize)
  {
  }

  bool AddKey(int Key)
  {
    int localDeInsercao = Key % Hash::Modulo;

    if (Hash::Counter == Hash::Modulo)
      return false;

    while (true)
    {
      if (Hash::IsEmpty[localDeInsercao])
      {
        Hash::array[localDeInsercao] = Key;
        Hash::IsEmpty[localDeInsercao] = false;
        Hash::Counter++;
        return true;
      }
      else
      {
        localDeInsercao++;
        localDeInsercao %= Hash::Modulo;
      }
    }
  }

  int *SearchKey(int Key)
  {
    int *Vetor_resposta = new int[2];

    int localDeBuscaInicial = Key % Hash::Modulo;
    int i;
    for (i = 1; i <= Hash::Modulo; i++)
    {
      if (Key == Hash::array[localDeBuscaInicial])
      {
        Vetor_resposta[0] = localDeBuscaInicial;
        Vetor_resposta[1] = i;
        return Vetor_resposta;
      }
      else if (Hash::IsEmpty[localDeBuscaInicial])
      {
        Vetor_resposta[0] = -1;
        Vetor_resposta[1] = i;
        return Vetor_resposta;
      }
      localDeBuscaInicial++;
      localDeBuscaInicial %= Hash::Modulo;
    }
    Vetor_resposta[0] = -1;
    Vetor_resposta[1] = i;
    return Vetor_resposta;
  }

  void PrintTable()
  {
    for (int i = 0; i < Hash::Modulo; i++)
    {
      if (Hash::IsEmpty[i])
        cout << " " << endl;
      else
        cout << Hash::array[i] << endl;
    }
  }
};