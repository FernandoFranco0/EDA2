class ListaEncadeada
{
private:
  struct No
  {
    int key;
    No *proximo;
  };

  No *CriarNo(int chave)
  {
    No *n = new No;
    n->key = chave;
    n->proximo = NULL;
    return n;
  }

public:
  No *head;
  No *tail;
  int Tamanho;

  ListaEncadeada()
  {
    head = new No;
    tail = new No;
    Tamanho = 0;
  }

  ~ListaEncadeada(){
    No *a = head;
    No *buffer = a->proximo;
    while(a != NULL){
      free(a);
      a = buffer;
      buffer = a->proximo;
    }
  }

  void AddKey(int chave)
  {
    No *n = CriarNo(chave);
    if (Tamanho == 0)
    {
      head = n;
      tail = n;
    }
    else
    {
      // cout << Tamanho << "tamanho2" << endl;
      tail->proximo = n;
      tail = n;
    }
    Tamanho++;
  }

  int SearchKey(int Key)
  {
    int i;
    No *buffer = head;
    for (i = 0; buffer->key != Key; i++)
    {
      buffer = buffer->proximo;
    }
    return i;
  }

  void printaLista()
  {
    if (Tamanho == 0)
      cout << endl;
    else
    {
      No *buffer = head;
      for (int i = 1; i < Tamanho; i++)
      {
        cout << buffer->key << " ";
        buffer = buffer->proximo;
      }
      cout << buffer->key << endl;
      buffer = nullptr;
      delete buffer;
    }
  }
};

class EncadeamentoExplicitoDinamico
{
public:
  vector<ListaEncadeada *> array;
  int Modulo;
  int Counter;

  EncadeamentoExplicitoDinamico(int HashSize)
  {
    Modulo = HashSize;
    Counter = 0;
    // array  = (ListaEncadeada*) malloc(sizeof(ListaEncadeada)*Modulo);
    for (int i = 0; i < Modulo; i++)
    {
      array.push_back(new ListaEncadeada());
    }
  }

  void AddKey(int Key)
  {
    int localDeInsercao = Key % Modulo;
    array[localDeInsercao]->AddKey(Key);
    Counter++;
  }

  int *SearchKey(int Key)
  {
    int *vetorRetorno = new int[3];
    int localDeInsercao = Key % Modulo;
    int busca = array[localDeInsercao]->SearchKey(Key);
    vetorRetorno[0] = localDeInsercao;
    vetorRetorno[2] = busca;

    vetorRetorno[1] = busca + 1;
    return vetorRetorno;
  }

  void PrintTable()
  {
    for (int i = 0; i < Modulo; i++)
    {
      cout << i << ": ";
      array[i]->printaLista();
    }
  }
};
