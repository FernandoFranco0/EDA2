// #include<bits/stdc++.h>
// #include "Hash.h"
using namespace std;

class DuploHashing : public Hash
{
public:
  DuploHashing(int HashSize) : Hash(HashSize)
  {
  }

  int Hash2(int Key)
  {
    if (Key < Modulo || Key % (Modulo * Modulo) == 0)
      return 1;
      
    return floor(Key / Hash::Modulo);
  }

  bool AddKey(int Key, int Sondagens = 0)
  {
    if (Sondagens == Hash::Modulo)
      return false;

    int localDeInsercao = ((Key % Hash::Modulo) + Hash2(Key) * Sondagens) % Hash::Modulo;

    if (!Hash::IsEmpty[localDeInsercao])
      return AddKey(Key, ++Sondagens);

    Hash::array[localDeInsercao] = Key;
    Hash::IsEmpty[localDeInsercao] = false;
    return true;
  }

  int Sondar(int Key, int &Contador, int Sondagens = 0)
  {

    if (Sondagens == Hash::Modulo)
      return -1;

    int localDeInsercao = ((Key % Hash::Modulo) + Hash2(Key) * Sondagens) % Hash::Modulo;

    if (!Hash::IsEmpty[localDeInsercao] && Hash::array[localDeInsercao] != Key)
      return Sondar(Key, ++Contador, ++Sondagens);

    return localDeInsercao;
  }

  int *SearchKey(int Key)
  {
    int *vetorResposta = new int[2];
    int Contador = 1;
    int posicao = Sondar(Key, Contador);

    vetorResposta[0] = posicao;
    vetorResposta[1] = Contador;

    return vetorResposta;
  }
};