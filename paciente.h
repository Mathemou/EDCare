#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Tipo opaco paciente*/
typedef struct paciente Paciente;

/*Aloca memória para um tipo paciente*/
Paciente * InicializaPaciente (char * nome);

/*Imprime o nome de um paciente*/
void ImprimePaciente (Paciente * paciente);

/*Libera a memória alocada para aquele paciente*/
void DestroiPaciente(Paciente* paciente);

/*Retorna um ponteiro para o nome do paciente (paciente->nome)*/
char * RetornaNomePaciente(Paciente * paciente);

/*Retorna se o paciente teve febre alta (2), baixa (1) ou não teve febre (0)*/
int Febre(Paciente * paciente);

/*Retorna o valor da latitude do paciente (paciente_>latitude*/
double RetornaLatitudePaciente(Paciente * paciente);

/*Retorna o valor da longitude do paciente (paciente_>longitude*/
double RetornaLongitudePaciente(Paciente * paciente);

/*Retorno booleano para se o paciente caiu ou não*/
int Caiu(Paciente * paciente);

/*Retorna a lista genérica de amigos daquele paciente passado como parâmetro (paciente->amigos*/
void * RetornaAmigos(Paciente * paciente);

/*Retorna a lista genérica de cuidadores do paciente passado como parâmetro (paciente->cuidadores)*/
void * RetornaCuidadores(Paciente * paciente);

/*Retorna o ponteiro para o arquivo contendo as informações do paciente ("nome do paciente".txt)*/
FILE * RetornaArquivoPaciente(Paciente * paciente);

/*Retorna o ponteiro para o arquivo que deve ser impresso as informações do paciente ("nome do paciente"-saida.txt)*/
FILE * RetornaArquivoSaidaPaciente(Paciente * paciente);

/*Retorno booleano para se o paciente está vivo ou não*/
int RetornaVivo(Paciente * paciente);

/*Retorno booleano se o paciente teve febre 4 vezes eguidas*/
int RetornaFebre4x(Paciente * paciente);

/*Adiciona paciente1 à lista de amigos de paciente2, bem como paciente2 na lista de amigos de paciente1*/
void * AdicionarAmigo(Paciente * paciente1, Paciente * paciente2);

/*Le uma linha do arquivo de informações ("nome do paciente".txt) e atualiza os dados do paciente*/
Paciente * LeLinhaPaciente(Paciente * paciente);

/*Aumenta o número de casos de febre baixa daquele paciente em um*/
void AumentaFebreBaixa(Paciente * paciente);

/*Zera os casos de febre baixa dquele paciente*/
void ZeraFebreBaixa(Paciente * paciente);
