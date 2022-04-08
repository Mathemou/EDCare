#include "cuidador.h"
#include "paciente.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Declaração de structs*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Tipo cuidador*/
struct cuidador{
  char * nome;
  double latitude;
  double longitude;
  FILE * arquivo;
};

/*Função para inicializar um elemnto do tipo cuidador*/
Cuidador * InicializaCuidador (char * nome){
  char nome_arquivo[50]="\0";
  strcat(nome_arquivo, nome);
  strcat(nome_arquivo, ".txt");
  Cuidador * cuidador = (Cuidador*) malloc (sizeof(Cuidador));
  cuidador->nome = strdup(nome);
  cuidador->arquivo = fopen(nome_arquivo, "r");
  if (cuidador->arquivo==NULL){
    printf("Arquivo %s de %s não encontrado", nome_arquivo, cuidador->nome);
    exit(0);
  }
  return cuidador;
}

/*Funções de impressão*/
/*Imprime o cuidador*/
void ImprimeCuidador (Cuidador * cuidador){
  printf("Nome do cuidador: %s\n", cuidador->nome);
}

/*Funções de destruição*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Destroi o cuidador, liberando memória*/
void DestroiCuidador(Cuidador* cuidador){
  fclose(cuidador->arquivo);
  free(cuidador->nome);
  free(cuidador);
}

/*Funções de retorno*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Retorna nome do cuidador*/
char * RetornaNomeCuidador(Cuidador * cuidador){
  return cuidador->nome;
}

/*Retorna latitude do cuidador*/
double RetornaLatitudeCuidador(Cuidador * cuidador){
  return cuidador->latitude;
}

/*Retorna longitude do cuidador*/
double RetornaLongitudeCuidador(Cuidador * cuidador){
  return cuidador->longitude;
}

/*Funções de atualizaçõa de dados*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Atualiza dados*/
Cuidador * LeLinhaCuidador(Cuidador * cuidador){
  char linha [100];
  double latitude;
  double longitude;
  if (fscanf(cuidador->arquivo,"%s\n", linha)==EOF){
    return NULL;
  } 
  sscanf(linha, "%lf;%lf", &cuidador->latitude, &cuidador->longitude);

  return cuidador;
}