#include "paciente.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*Definição de structs*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
struct paciente{
  char * nome;
  float temperatura;
  double latitude;
  double longitude;
  int queda;
  int vivo;
  Lista * amigos;
  Lista * cuidadores;
  FILE * arquivo;
  FILE * arquivoSaida;
  int cont_febre_baixa;
};

/*Funções de inicialização*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Inicializa uma variavél do tipo Paciente*/
Paciente * InicializaPaciente (char * nome){
  char nome_arquivo[50] = "\0";
  char nome_arquivo_saida[50] = "\0";
  /*Organiza strings de arquivos de entrada e saída*/
  strcat(nome_arquivo, nome);
  strcat(nome_arquivo_saida, nome);
  strcat(nome_arquivo_saida, "-saida.txt");
  strcat(nome_arquivo, ".txt");
  /*Começa a alocar memoria e definir variaveis*/
  Paciente * paciente = (Paciente*) malloc (sizeof(Paciente));
  paciente->nome = strdup(nome);
  paciente->amigos = InicLista();
  paciente->cuidadores = InicLista();
  
  paciente->arquivo = fopen(nome_arquivo, "r");
  if (paciente->arquivo==NULL){
    printf("Arquivo %s de %s não encontrado", nome_arquivo, paciente->nome);
    exit(0);
  }
  paciente->arquivoSaida = fopen(nome_arquivo_saida, "w");
  paciente->vivo=1;
  paciente->cont_febre_baixa=0;
  return paciente;
}

/*Funções de impressão*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Imprime o nome do paciente*/
void ImprimePaciente (Paciente * paciente){
  printf("Nome do paciente: %s\n", paciente->nome);
}

//Funções de destruição*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Libera memória alocada pra aquele paciente*/
void DestroiPaciente(Paciente* paciente){
  fclose(paciente->arquivo);
  fclose(paciente->arquivoSaida);
  free(paciente->nome);
  free(paciente);
}

/*Funções de retorno*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Retorna o nome do paciente*/
char * RetornaNomePaciente(Paciente * paciente){
  return paciente->nome;
}

/*Retorna se o paciente está com febre baixa, alta ou não está com febre*/
int Febre(Paciente * paciente){
  if(paciente->temperatura>=37&&paciente->temperatura<=38){
    return 1;
  } else if (paciente->temperatura>38){
    return 2;
  } else {
    return 0;
  }
}

/*Retorna a latitude do paciente*/
double RetornaLatitudePaciente(Paciente * paciente){
  return paciente->latitude;
}

/*Retorna a longitude do paciente*/
double RetornaLongitudePaciente(Paciente * paciente){
  return paciente->longitude;
}

/*Retorna verdadeiro de o paciente caiu*/
int Caiu(Paciente * paciente){
  return paciente->queda;
}

/*Retorna lista de amigos do paciente*/
void * RetornaAmigos(Paciente * paciente){
  return paciente->amigos;
}

/*Retorna lista de cuidadores do paciente*/
void * RetornaCuidadores(Paciente * paciente){
  return paciente->cuidadores;
}

/*Retorna o arquivo nome.txt referente a aquele paciente passado como parâmetro*/
FILE * RetornaArquivoPaciente(Paciente * paciente){
  return paciente->arquivo;
}

/*Retorna o arquivo nome-saida.txt referente a aquele paciente passado como parâmetro*/
FILE * RetornaArquivoSaidaPaciente(Paciente * paciente){
  return paciente->arquivoSaida;
}

/*Retorna se o paciente está vivo*/
int RetornaVivo(Paciente * paciente){
  return paciente->vivo;
}

/*Retorna se o paciente teve febre 3x seguidas*/
int RetornaFebre4x(Paciente * paciente){
 if(paciente->cont_febre_baixa==3){
   return 1;
 } else {
   return 0;
 }
}

/*Funções de adição*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Adiciona mutuamente os amigos para os pacientes*/
void * AdicionarAmigo(Paciente * paciente1, Paciente * paciente2){
  InsereListaPacientes(paciente1->amigos, paciente2);
  InsereListaPacientes(paciente2->amigos, paciente1);
  return 0;
}

/*Função de leitura de arquivo*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Le uma linha do arquivo nome.txt do paciente*/
Paciente * LeLinhaPaciente(Paciente * paciente){
  char linha [100];
  float temperatura;
  double latitude;
  double longitude;
  int queda;
  if (fscanf(paciente->arquivo,"%s\n", linha)==EOF){
    return NULL;
  } 
  if (strcmp(linha, "falecimento")==0) {
    //printf("%s faleceu...\n\n", paciente->nome);
    paciente->vivo=0;
  }else{
  sscanf(linha, "%f;%lf;%lf;%d", &paciente->temperatura, &paciente->latitude, &paciente->longitude, &paciente->queda);
  
  }
  return paciente;
}

/*Funções de modificação*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Aumenta em um o contador de febre baixa*/
void AumentaFebreBaixa(Paciente * paciente){
  paciente->cont_febre_baixa++;
}

/*Zera o contador de febre baixa*/
void ZeraFebreBaixa(Paciente * paciente){
  paciente->cont_febre_baixa=0;
}





































//printf("Temperatura de %s: %.2f\nLatitude de %s: %ld\nLongitude de %s: %ld\n", RetornaNomePaciente(paciente), temperatura, RetornaNomePaciente(paciente), latitude, RetornaNomePaciente(paciente), longitude);

  /*if(queda == 0){
    printf("%s não caiu...\n\n", RetornaNomePaciente(paciente));
  } else {
    printf("%s caiu!\n\n", RetornaNomePaciente(paciente));
  }*/