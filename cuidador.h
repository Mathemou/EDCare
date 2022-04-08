#include "paciente.h"

/*Tipo opaco cuidador*/
typedef struct cuidador Cuidador;

/*Aloca espaço para um ponteiro do tipo cuidador*/
Cuidador * InicializaCuidador (char * nome);

/*Imprime o cuidador*/
void ImprimeCuidador (Cuidador * cuidador);

/*Libera a memória alocado parao tipo cuidador*/
void DestroiCuidador(Cuidador* cuidador);

/*Retorna um ponteiro para o nome do cuidador (cuidador->nome)*/
char * RetornaNomeCuidador(Cuidador * paciente);

/*Retornao valor da latitude do cuidador (cuidador->latitude)*/
double RetornaLatitudeCuidador(Cuidador * cuidador);

/*Retornao valor da longitude do cuidador (cuidador->longitude)*/
double RetornaLongitudeCuidador(Cuidador * cuidador);

/*Le a linha pela entrada do arquivo "nome do cuidador".txt e armazena essas informações no tipo cuidador*/
Cuidador * LeLinhaCuidador(Cuidador * cuidador);