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
#include "./hashing/linear.h"

void Conjuntos(int, int, string, int);
void ArquivoInteiro(int, int);



int main()
{
  long double alfa = 2;
  
  string TestFileName;
  int HashSize, SetAmount;
  ofstream Resultados;


  linear h(80);

  h.AddKey(8);
  h.AddKey(11);
  h.AddKey(10);
  h.AddKey(15);
  h.AddKey(17);
  h.AddKey(25);
  h.AddKey(44);
  h.AddKey(12);


  cout << "a";



  // -----------------------------Testar dps------------------------
  // cout << "Tamnaho da Hash: ";
  // cin >> HashSize;
  // cout << "Nome do arquivo de teste:  ";
  // getline(cin,TestFileName);
  // cout << "Número de conjuntos de teste no arquivo:  ";
  // cin >> SetAmount;

  TestFileName = "testes/testes-finais/testes-finais-0.txt";
  HashSize = 1001;
  SetAmount = 100;

  int Caso = 1;

  switch (Caso)
  {
  case 1:
    Resultados.open("Saida-explicito-estatico.csv");
    Resultados << "\"Conjunto\",\"Alfa\",\"Acesso-Medio\"" << endl;
    Resultados.close();

    Resultados.open("Saida-explicito-dinamico.csv");
    Resultados << "\"Conjunto\",\"Alfa\",\"Acesso-Medio\"" << endl;
    Resultados.close();

    Resultados.open("Saida-Duplo-hashing.csv");
    Resultados << "\"Conjunto\",\"Alfa\",\"Acesso-Medio\"" << endl;
    Resultados.close();

    Resultados.open("Saida-Sondagem-linear.csv");
    Resultados << "\"Conjunto\",\"Alfa\",\"Acesso-Medio\"" << endl;
    Resultados.close();

    for (int i = 0; i < SetAmount; i++)
    {
      for (int j = 1; j < 50; j++)
      {
        Conjuntos(alfa*j, i, TestFileName, HashSize);
      }
    }

    break;
  
  case 2:

    Resultados.open("Saida-explicito-estatico-total.csv");
    Resultados << "\"Alfa\",\"Acesso-Medio\"" << endl;
    Resultados.close();

    Resultados.open("Saida-explicito-dinamico-total.csv");
    Resultados << "\"Alfa\",\"Acesso-Medio\"" << endl;
    Resultados.close();

    Resultados.open("Saida-Duplo-hashing-total.csv");
    Resultados << "\"Alfa\",\"Acesso-Medio\"" << endl;
    Resultados.close();

    Resultados.open("Saida-Sondagem-linear-total.csv");
    Resultados << "\"Alfa\",\"Acesso-Medio\"" << endl;
    Resultados.close();

    for (int j = 1; j < 50; j++)
    {
      ArquivoInteiro(alfa*j, SetAmount);
    }
    break;

  default:
    break;
  }


  //TestaCasosDaAula(4);

  return 0;
}

void Conjuntos(int Alfa, int SetNumber, string TestFileName, int HashSize){
  long double *vetor;
  ofstream Resultados;

  vetor = MediaDeAcessosConjunto(Alfa, SetNumber, TestFileName, HashSize);

  cout << fixed << setprecision(5);
  cout << "=-=-=-=-=-=-=-=alfa-" << Alfa << "=-=-=-=-=-=-=-=" << endl;

  cout << "Media de acessos dos metodos para o conjunto " << SetNumber + 1 << endl;

  cout << "Encadeamento explicito dinamico: " << setw(7) << vetor[0] << endl;
  Resultados.open("Saida-explicito-dinamico.csv", ios_base::app);
  Resultados << SetNumber << "," << Alfa << "," << vetor[0] << endl;
  Resultados.close();

  cout << "Encadeamento explicito estatico: " << setw(7) << vetor[1] << endl;
  Resultados.open("Saida-explicito-estatico.csv", ios_base::app);
  Resultados << SetNumber << "," << Alfa << "," << vetor[1] << endl;
  Resultados.close();

  cout << left << setw(31) << "Duplo hashing" << ": " << right << setw(7) << vetor[2] << endl;
  Resultados.open("Saida-Duplo-hashing.csv", ios_base::app);
  Resultados << SetNumber << "," << Alfa << "," << vetor[2] << endl;
  Resultados.close();

  cout << left << setw(31) << "Sondagem linear" << ": " << right << setw(7) << vetor[3] << endl;
  Resultados.open("Saida-Sondagem-linear.csv", ios_base::app);
  Resultados << SetNumber << "," << Alfa << "," << vetor[3] << endl;
  Resultados.close();

  cout << endl;
}

void ArquivoInteiro(int Alfa, int SetAmount){
  long double *vetor;
  ofstream Resultados;



  vetor = MediaDeAcessosArquivo(Alfa, SetAmount);
  cout << fixed << setprecision(2);
  cout << "=-=-=-=-=-=-=-=alfa-" << Alfa << "=-=-=-=-=-=-=-=" << endl;
  cout << "=-=-=-Media de acessos dos metodos=-=-=-" << endl;

  cout << "Encadeamento explicito dinamico: " << setw(7) << vetor[0] << endl;
  Resultados.open("Saida-explicito-dinamico-total.csv", ios_base::app);
  Resultados << Alfa << "," << vetor[0] << endl;
  Resultados.close();

  cout << "Encadeamento explicito estatico: " << setw(7) << vetor[1] << endl;
  Resultados.open("Saida-explicito-estatico-total.csv", ios_base::app);
  Resultados << Alfa << "," << vetor[1] << endl;
  Resultados.close();

  cout << left << setw(31) << "Duplo hashing" << ": " << right << setw(7) << vetor[2] << endl;
  Resultados.open("Saida-Duplo-hashing-total.csv", ios_base::app);
  Resultados << Alfa << "," << vetor[2] << endl;
  Resultados.close();

  cout << left << setw(31) << "Sondagem linear" << ": " << right << setw(7) << vetor[3] << endl;
  Resultados.open("Saida-Sondagem-linear-total.csv", ios_base::app);
  Resultados << Alfa << "," << vetor[3] << endl;
  Resultados.close();
}