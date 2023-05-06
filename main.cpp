#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

#include "./hashing/Hash.h"
#include "./hashing/encadeamento-explicito-dinamico.h"
#include "./hashing/encadeamento-explicito.h"
#include "./hashing/enderecamento-aberto-duplo-hashing.h"
#include "./hashing/enderecamento-aberto-sondagem-linear.h"
#include "./testes/funcoes-de-teste.h"

int main()
{
  float alfa = 2;
  float *vetor;
  string TestFileName;
  int HashSize, SetAmount;
  ofstream Resultados;

  // -----------------------------Testar dps------------------------
  // cout << "Tamnaho da Hash: ";
  // cin >> HashSize;
  // cout << "Nome do arquivo de teste:  ";
  // getline(cin,TestFileName);
  // cout << "Número de conjuntos de teste no arquivo:  ";
  // cin >> SetAmount;

  TestFileName = "testes/testes-finais/testes-finais-0.txt";
  HashSize = 997;
  SetAmount = 100;


  Resultados.open("Saida-explicito-estatico.txt");
  Resultados << "\"Conjunto\",\"Alfa\",\"Acesso-Medio\"" << endl;
  Resultados.close();

  Resultados.open("Saida-explicito-dinamico.txt");
  Resultados << "\"Conjunto\",\"Alfa\",\"Acesso-Medio\"" << endl;
  Resultados.close();

  Resultados.open("Saida-Duplo-hashing.txt");
  Resultados << "\"Conjunto\",\"Alfa\",\"Acesso-Medio\"" << endl;
  Resultados.close();

  Resultados.open("Saida-Sondagem-linear.txt");
  Resultados << "\"Conjunto\",\"Alfa\",\"Acesso-Medio\"" << endl;
  Resultados.close();

  for (int i = 0; i < SetAmount; i++)
  {
    for (int j = 1; j < 50; j++)
    {
      vetor = MediaDeAcessosConjunto(alfa * j, i, TestFileName, HashSize);

      cout << fixed << setprecision(5);
      cout << "=-=-=-=-=-=-=-=alfa-" << alfa * j << "=-=-=-=-=-=-=-=" << endl;

      cout << "Media de acessos dos metodos para o conjunto " << i + 1 << endl;

      cout << "Encadeamento explicito estatico: " << setw(7) << vetor[0] << endl;
      Resultados.open("Saida-explicito-estatico.txt", ios_base::app);
      Resultados << i << "," << alfa * j << "," << vetor[0] << endl;
      Resultados.close();

      cout << "Encadeamento explicito dinamico: " << setw(7) << vetor[1] << endl;
      Resultados.open("Saida-explicito-dinamico.txt", ios_base::app);
      Resultados << i << "," << alfa * j << "," << vetor[1] << endl;
      Resultados.close();

      cout << left << setw(31) << "Duplo hashing" << ": " << right << setw(7) << vetor[2] << endl;
      Resultados.open("Saida-Duplo-hashing.txt", ios_base::app);
      Resultados << i << "," << alfa * j << "," << vetor[2] << endl;
      Resultados.close();

      cout << left << setw(31) << "Sondagem linear" << ": " << right << setw(7) << vetor[3] << endl;
      Resultados.open("Saida-Sondagem-linear.txt", ios_base::app);
      Resultados << i << "," << alfa * j << "," << vetor[3] << endl;
      Resultados.close();

      cout << endl;
    }
  }

  // int numero_de_casos = 8;
  // float alfa_inicial = 99;
  // float incremento;

  // if (numero_de_casos > 1) {
  //   incremento = (99.99999 - alfa_inicial) / (numero_de_casos - 1);
  // } else {
  //   incremento = 0;
  // }

  // for (float i = 0; i < numero_de_casos; i++) {
  //   alfa = alfa_inicial + i * incremento;
  //   vetor = MediaDeAcessosArquivo(alfa);

  //   cout << fixed << setprecision(2);
  //   cout << "=-=-=-=-=-=-=-=alfa-" << alfa << "=-=-=-=-=-=-=-=" << endl;
  //   cout << "=-=-=-Media de acessos dos metodos=-=-=-" << endl;
  //   cout << "Encadeamento explicito estatico: " << setw(7) << vetor[0] << endl;
  //   cout << "Encadeamento explicito dinamico: " << setw(7) << vetor[1] << endl;
  //   cout << left << setw(31) << "Duplo hashing" << ": " << right << setw(7) << vetor[2] << endl;
  //   cout << left << setw(31) << "Sondagem linear" << ": " << right << setw(7) << vetor[3] << endl;

  //   cout << endl;
  // }

  return 0;
}