
void AbrirLinear(string Nome){
  ifstream CasoTeste;
  CasoTeste.open(Nome);
  
  int Modulo, Quantidade;

  CasoTeste >> Quantidade;
  CasoTeste >> Modulo;
  
  int *Keys;
  Keys = new int[Modulo];
  
  for (int i = 0; i < Quantidade; i++) {
    CasoTeste >> Keys[i];
  }

  SondagemLinear h(Modulo);

  for(int i = 0 ; i < Quantidade ; i++){
    h.AddKey(Keys[i]);
  }
  
  h.PrintTable();
  
}

void AbrirDuplo(string Nome){
  ifstream CasoTeste;
  CasoTeste.open(Nome);
  
  int Modulo, Quantidade;

  CasoTeste >> Quantidade;
  CasoTeste >> Modulo;
  
  int *Keys;
  Keys = new int[Modulo];
  
  for (int i = 0; i < Quantidade; i++) {
    CasoTeste >> Keys[i];
  }

  DuploHashing h(Modulo);

  for(int i = 0 ; i < Quantidade ; i++){
    h.AddKey(Keys[i]);
  }

  h.PrintTable();
  
}

void AbrirExplicito(string Nome){
  ifstream CasoTeste;
  CasoTeste.open(Nome);
  
  int Modulo, Quantidade;

  CasoTeste >> Quantidade;
  CasoTeste >> Modulo;
  
  int *Keys;
  Keys = new int[Modulo];
  
  for (int i = 0; i < Quantidade; i++) {
    CasoTeste >> Keys[i];
  }

  EncadeamentoExplicito h(Modulo);

  for(int i = 0 ; i < Quantidade ; i++){
    h.AddKey(Keys[i]);
  }
  
  cout << endl;
  h.PrintTable();
  
}

void AbrirExplicitoDinamico(string Nome){
  ifstream CasoTeste;
  CasoTeste.open(Nome);
  
  int Modulo, Quantidade;

  CasoTeste >> Quantidade;
  CasoTeste >> Modulo;
  
  int *Keys;
  Keys = new int[Modulo];
  
  for (int i = 0; i < Quantidade; i++) {
    CasoTeste >> Keys[i];
  }

  EncadeamentoExplicitoDinamico h(Modulo);

  for(int i = 0 ; i < Quantidade ; i++){
    h.AddKey(Keys[i]);
  }
  h.PrintTable();
  
}

void TestaCasosDaAula(int HashType){

  string Nome;
  switch(HashType){
    case 1:
       Nome = "testes/testes-especificos/teste-duplo.txt";
       AbrirDuplo(Nome);
      break;
    case 2:
      Nome = "testes/testes-especificos/teste-explicito.txt";
      AbrirExplicito(Nome);
      break;
     case 3:
       Nome = "testes/testes-especificos/teste-sondagem.txt";
       AbrirLinear(Nome);
       break;
      case 4:
        Nome = "testes/testes-especificos/teste-explicito.txt";
        AbrirExplicitoDinamico(Nome);
        break;
  }
  
}

float *MediaDeAcessosArquivo(float alfa, int SetAmount){
    
  string Nome;
  int *chaves = new int[int(1001*alfa/100)];
  
  float *MediaDeUmArquivo = (float*) calloc(4,sizeof(float));//Media de todos as chaves de uma tabela de todas as tabelas de um arquivo de teste
  float *MediaDeUmConjunto = (float*) calloc(4,sizeof(float));//Media de todos as chaves de uma tabela
  ifstream CasoTeste;
  int j, i;
  int buffer;
  //Calcula a media de todos os arquivos

    //abre arquivo
    Nome = "testes/testes-finais/testes-finais-0.txt";
    CasoTeste.open(Nome);
  
    //analisa todo conjunto
    for( j = 0; j < SetAmount; j++){

      //coleta as 1001*alfa/100 chaves a serem inseridas
      for( i = 0; i < 1001 ; i ++){
        
        if (i < 1001*alfa/100){             
          CasoTeste >> chaves[i];
        }
        else{
          CasoTeste >> buffer;
        }
      }
      
      //declara cria as tabelas hash
      EncadeamentoExplicitoDinamico h0(1001);
      EncadeamentoExplicito h1(1001);
      DuploHashing h2(1001);
      SondagemLinear h3(1001);
      
      //adicionas as chaves a suas posições respectivas
      for( i = 0; i < 1001*alfa/100; i ++){
        h0.AddKey(chaves[i]);
        h1.AddKey(chaves[i]);
        h2.AddKey(chaves[i]);
        h3.AddKey(chaves[i]);
      }
      
      MediaDeUmConjunto[0] = 0;
      MediaDeUmConjunto[1] = 0;
      MediaDeUmConjunto[2] = 0;
      MediaDeUmConjunto[3] = 0;

      //calcula media de um conjunto
      for( i = 0; i < 1001*alfa/100; i ++){
        MediaDeUmConjunto[0] += h0.SearchKey(chaves[i])[1];
        MediaDeUmConjunto[1] += h1.SearchKey(chaves[i])[1];
        MediaDeUmConjunto[2] += h2.SearchKey(chaves[i])[1];
        MediaDeUmConjunto[3] += h3.SearchKey(chaves[i])[1];
      }
      
      MediaDeUmConjunto[0] /= (1001*alfa/100);
      MediaDeUmConjunto[1] /= (1001*alfa/100);
      MediaDeUmConjunto[2] /= (1001*alfa/100);
      MediaDeUmConjunto[3] /= (1001*alfa/100);

      
      MediaDeUmArquivo[0] += MediaDeUmConjunto[0];
      MediaDeUmArquivo[1] += MediaDeUmConjunto[1];
      MediaDeUmArquivo[2] += MediaDeUmConjunto[2];
      MediaDeUmArquivo[3] += MediaDeUmConjunto[3];
      
    }
    
    MediaDeUmArquivo[0] /= SetAmount;
    MediaDeUmArquivo[1] /= SetAmount;
    MediaDeUmArquivo[2] /= SetAmount;
    MediaDeUmArquivo[3] /= SetAmount;

  CasoTeste.close();
  
  return MediaDeUmArquivo;
}

float *MediaDeAcessosConjunto(float alfa, int NumeroConjunto, string TestFileName, int HashSize){
  
  int chaves[int(HashSize*alfa/100)];

  float *MediaDeUmConjunto = (float*) calloc(4,sizeof(float));//Media de todos as chaves de uma tabela

  
  ifstream CasoTeste;
  int i;
  int buffer;
  //Calcula a media de todos os arquivos

  //abre arquivo
  CasoTeste.open(TestFileName);

  //ineficiente ? Sim, mas funciona
  for(int i = 0 ; i < NumeroConjunto*HashSize; i++){
    CasoTeste >> buffer;
  }

  //analisa todo conjunto

  //coleta as 1001*alfa/100 chaves a serem inseridas
  for( i = 0; i < HashSize ; i ++){
     if (i < HashSize*alfa/100){             
       CasoTeste >> chaves[i];
     }
     else{
       CasoTeste >> buffer;
     }
   }

  // //declara cria as tabelas hash
  EncadeamentoExplicitoDinamico h0(HashSize);
  EncadeamentoExplicito h1(HashSize);
  DuploHashing h2(HashSize);
  SondagemLinear h3(HashSize);
  
  // //adicionas as chaves a suas posições respectivas
  for( i = 0; i < HashSize*alfa/100; i++){
    h0.AddKey(chaves[i]);
    h1.AddKey(chaves[i]);
    h2.AddKey(chaves[i]);
    h3.AddKey(chaves[i]);
  }
  
  //
  
  //calcula media de um conjunto
  for( i = 0; i < HashSize*alfa/100; i ++){
    MediaDeUmConjunto[0] += h0.SearchKey(chaves[i])[1];
    MediaDeUmConjunto[1] += h1.SearchKey(chaves[i])[1];
    MediaDeUmConjunto[2] += h2.SearchKey(chaves[i])[1];
    MediaDeUmConjunto[3] += h3.SearchKey(chaves[i])[1];
  }
  
  MediaDeUmConjunto[0] /= (HashSize*alfa/100);
  MediaDeUmConjunto[1] /= (HashSize*alfa/100);
  MediaDeUmConjunto[2] /= (HashSize*alfa/100);
  MediaDeUmConjunto[3] /= (HashSize*alfa/100); 
  

  CasoTeste.close();
  
  return MediaDeUmConjunto;
}
