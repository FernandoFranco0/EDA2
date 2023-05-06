// #include<bits/stdc++.h>
// #include "Hash.h"

class EncadeamentoExplicito : public Hash
{
public:
  int *pointerArray;
  int bottomPointer;

  EncadeamentoExplicito(int HashSize) : Hash(HashSize)
  {
    pointerArray = new int[HashSize];
    bottomPointer = HashSize - 1;
    for (int i = 0; i < HashSize; i++)
    {
      pointerArray[i] = -1;
    }
  }

  bool AddKey(int Key)
  {
    int localDeInsercao = Key % Hash::Modulo;

    if (Hash::Counter == Hash::Modulo)
      return false;

    if (Hash::IsEmpty[localDeInsercao])
    {
      Hash::array[localDeInsercao] = Key;
      Hash::IsEmpty[localDeInsercao] = false;

      if (localDeInsercao == bottomPointer)
      {
        while (Hash::IsEmpty[bottomPointer] == false)
        {
          bottomPointer--;
        }
      }
    }
    else
    {

      Hash::array[bottomPointer] = Key;

      int i = localDeInsercao; // segue cadeia de ponteiros
      while (pointerArray[i] != -1)
      {
        i = pointerArray[i];
      }
      pointerArray[i] = bottomPointer; // insere referencia do elementos no local

      Hash::IsEmpty[bottomPointer] = false;

      while (Hash::IsEmpty[bottomPointer] == false)
      {
        bottomPointer--;
      }
    }
    Hash::Counter++;
    return true;
  }

  int *SearchKey(int Key)
  {
    int localDeInsercao = Key % Hash::Modulo;
    int *Vetor_resposta = new int[2];

    int contador = 1;
    if (Hash::array[localDeInsercao] != Key && Hash::IsEmpty[localDeInsercao] == false)
    {
      int i = pointerArray[localDeInsercao];
      for (; Hash::array[i] != Key; contador++)
      {
        if (pointerArray[i] == -1)
        {
          i = -1;
          break;
        }
        i = pointerArray[i];
      }
      contador++;
      Vetor_resposta[0] = i;
      Vetor_resposta[1] = contador;
      return Vetor_resposta;
    }

    Vetor_resposta[0] = localDeInsercao;
    Vetor_resposta[1] = contador;
    return Vetor_resposta;
  }

  void PrintTable()
  {
    for (int i = 0; i < Hash::Modulo; i++)
    {
      cout << i << ": ";
      if (Hash::IsEmpty[i])
        cout << "(  | )" << endl;
      else
      {
        if (pointerArray[i] != -1)
          cout << "(" << Hash::array[i] << "|" << pointerArray[i] << ")" << endl;
        else
          cout << "(" << Hash::array[i] << "| )" << endl;
      }
    }
  }
};
