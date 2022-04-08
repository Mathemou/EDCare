#include "lista.h"
#include "paciente.h"
#include "cuidador.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

/*Declaração de stricts*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Tipo célula*/
typedef struct cel Celula;

struct cel {
  void * item;
  Celula * prox;
};

/*Tipo lista*/
typedef struct lista Lista;

struct lista {
  Celula * prim;
  Celula * ult;
};

Celula * RetornaPrimeraCelula(Lista * lista){
    return lista->prim;
}

/*Funções d einicialização*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Inicia lista*/
Lista * InicLista(){
  Lista * lista = (Lista*) malloc (sizeof(Lista));
  lista->prim = NULL;
  lista->ult=NULL;
  return lista; 
}

/*Funções de inserção*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Insere um paciente em uma lista de pacientes*/
void InsereListaPacientes(Lista* lista, Paciente * paciente){
  Celula * nova = (Celula*) malloc (sizeof(Celula));
  nova->item = paciente;
  nova->prox = lista->prim;
  lista->prim = nova;
  if (lista->ult==NULL){
    lista->ult = nova;
  }
  
}

/*Insere um cuidador na lista de cuidadores*/
void InsereListaCuidador(Lista * lista, Cuidador * cuidador){
  Celula * nova = (Celula*) malloc (sizeof(Celula));
  nova->item = cuidador;
  nova->prox = lista->prim;
  lista->prim = nova;
  if (lista->ult==NULL){
    lista->ult = nova;
  }
  
}

/*Funções de impressão*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Imprime a lista apenas com os nomes dos pacientes*/
void ImprimeListaPacientes(Lista * lista){
  Celula * p;
  printf("Lista de pacientes:\n");
  for(p = lista->prim; p!=NULL; p = p->prox){
    ImprimePaciente((Paciente*)p->item);
  }
  printf("\n");
}

/*Imprime a lista apenas com nomes dos cuidadores*/
void ImprimeListaCuidadores(Lista* lista){
  Celula * p;
  printf("Lista de cuidadores:\n");
  for(p = lista->prim; p!=NULL; p = p->prox){
    ImprimeCuidador((Cuidador*)p->item);
  }
  printf("\n");
}

/*Imprime os cuidadores daquele paciente*/
void ImprimePacientesECuidadores (Lista * pacientes){
  Celula * p;
  for(p = pacientes->prim; p!=NULL; p = p->prox){
    ImprimePaciente(p->item);
    Lista * lista_cuidadores = RetornaCuidadores(p->item);
    Celula * p2;
    for(p2=lista_cuidadores->prim;p2!=NULL;p2=p2->prox){
      ImprimeCuidador(p2->item);
    }
  }
  printf("\n");
}

/*Funções de retirada*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Paciente * RetiraLista(Lista * lista, char * chave){
  Celula * p = lista->prim;
  Paciente * exc;
  Celula * ant = NULL;

  while (p!=NULL && strcmp (RetornaNomePaciente(p->item), chave)){
    ant = p;
    p = p->prox;
  }

  if (p==NULL){
    return NULL;
  }

  exc = p->item;

  if (p== lista->prim && p == lista->ult){
    lista->prim = lista->ult = NULL;
  } else if (p==lista->prim){
    lista->prim = p->prox;
  } else if (p==lista->ult){
    lista->ult = ant;
    lista->ult->prox = NULL;
  } else {
    ant->prox = p->prox;
  }

    DestroiPaciente(exc);
    DestroiListaDeAmigos(exc);
    DestroiListaDeCuidadores(exc);
    free(p);

  return exc;
}

/*Funções de destruição*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Libera a memória alocada para as listas e para os pacientes*/
void DestroiListaPacientes(Lista* lista){
    Celula * p = lista->prim;
    Celula * t;

  while (p!=NULL){
    t = p->prox;
    DestroiListaDeAmigos(p->item);
    DestroiListaDeCuidadores(p->item);
    DestroiPaciente(p->item);
    free(p);
    p = t;
  }

  free(lista);
}

void DestroiListaDeAmigos(Paciente * paciente){
    Celula * p=RetornaPrimeraCelula(RetornaAmigos(paciente));
    Celula * t;
    while(p!=NULL){
        t = p;
        p=p->prox;
        free(t);
    }
    free(RetornaAmigos(paciente));
}

void DestroiListaDeCuidadores(Paciente * paciente){
    Celula * p=RetornaPrimeraCelula(RetornaCuidadores(paciente));
    Celula * t;
    while(p!=NULL){
        t = p;
        p=p->prox;
        free(t);
    }
    free(RetornaCuidadores(paciente));
}

/*Libera a memória alocada para as listas e para os pacientes*/
void DestroiListaCuidadores(Lista* lista){
  Celula * p = lista->prim;
  Celula * t;

  while (p!=NULL){
    t = p->prox;
    DestroiCuidador((Cuidador*)p->item);
    free(p);
    p = t;
  }

  free(lista);
}

//Funções de busca*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*Busca um paciente pelo nome*/
void * BuscaPaciente (Lista * lista, char * chave){
  Celula * cel;
  for(cel = lista->prim; cel!=NULL; cel = cel->prox){
    if(strcmp(RetornaNomePaciente(cel->item), chave)==0){
      return cel->item;
    }
  }
  return NULL;
}

void * BuscaCuidador (Lista * lista, char * chave){
  Celula * cel;
  for(cel = lista->prim; cel!=NULL; cel = cel->prox){
    if(strcmp(RetornaNomeCuidador(cel->item), chave)==0){
      return cel->item;
    }
  }
  return NULL;
}

/*Funções de localização*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double CoeficienteDistanciaPacientes(Paciente * paciente1, Paciente * paciente2){
  double cd;
  double lat, lon;
  lat = RetornaLatitudePaciente(paciente1) - RetornaLatitudePaciente(paciente2);
  lon = RetornaLongitudePaciente(paciente1) - RetornaLatitudePaciente(paciente2);
  if (lat<0){
    lat*=-1;
  }
  if (lon<0){
    lon*=-1;
  }
  cd = pow(lat, 2) + pow(lon, 2);
  cd = sqrt(cd);
  return cd;
}

double CoeficienteDistanciaCuidador(Paciente * paciente, Cuidador * cuidador){
  double cd;
  double lat, lon;
  lat = RetornaLatitudePaciente(paciente) - RetornaLatitudeCuidador(cuidador);
  lon = RetornaLongitudePaciente(paciente) - RetornaLongitudeCuidador(cuidador);
  if (lat<0){
    lat*=-1;
  }
  if (lon<0){
    lon*=-1;
  }
  cd = pow(lat, 2) + pow(lon, 2);
  cd = sqrt(cd);
  return cd;
}

/*Função que retorna o amigo mais próximo do paciente passado como argumento*/
Paciente * AmigoMaisProximo(Paciente * paciente){
  Celula * p;
  Paciente * paciente_proximo = NULL;
  /*Variavel que armazena o maior valor possível de um double, sendo assim,qualquer double será menor que ele*/
  double menor_distancia =  2147483647;
  /*Lista de amigos do paciente*/
  Lista * lista = RetornaAmigos(paciente);
  /*Loop que pega cada amigo do paciente e verifica se ele está mais próximo que o anterior*/
  for(p=lista->prim; p!= NULL; p=p->prox){
    if(CoeficienteDistanciaPacientes(paciente, p->item)<menor_distancia&&RetornaVivo(p->item)){
      menor_distancia = CoeficienteDistanciaPacientes(paciente, p->item);
      paciente_proximo = p->item;
    }
  }
  return paciente_proximo;
}

/*Função que retorna o cuidador mais proximo do paciente passado como argumento*/
Cuidador * CuidadorMaisProximo(Paciente * paciente){
  Celula * p;
  Cuidador * cuidador_proximo = NULL;
  /*Variavel que armazena o maior valor possível de um double, sendo assim,qualquer double será menor que ele*/
  double menor_distancia =  2147483647;
  /*Lista de amigos do paciente*/
  Lista * lista = RetornaCuidadores(paciente);
  /*Loop que pega cada cuidador do paciente e verifica se ele está mais próximo que o anterior*/
  for(p=lista->prim; p!= NULL; p=p->prox){
    if(CoeficienteDistanciaCuidador(paciente, p->item)<menor_distancia){
      menor_distancia = CoeficienteDistanciaCuidador(paciente, p->item);
      cuidador_proximo = p->item;
    }
  }
  return cuidador_proximo;
}

/*Função de leitura de dados*/
/*Atualiza os dados(Temperatura, latitude, longitude e queda) de todos os pacientes*/
void Leitura(Lista * lista, Lista * cuidadores){
  Celula * p;
  int achou_morto=0;

  /*Loop de leitura dos dados, que só se encerra quando um dos arquivos de umpaciente encontra o EOF (retorna NULL*/
  while (1){

  /*Loop para ler cada linha de cada paciente por vez*/
  for(p = lista->prim; p!=NULL; p = p->prox){
    
    if(LeLinhaPaciente(p->item)==NULL){
      return;
    }
    
  }

  /*Loop para ler cada linha de cada cuidador por vez*/
  for(p = cuidadores->prim; p!=NULL; p= p->prox){
    if(LeLinhaCuidador(p->item)==NULL){
      return;
    }
  }

  /*Loop para retirar pacientes mortos*/
  do{
    achou_morto=0;
  for(p = lista->prim; p!=NULL; p = p->prox){
    if (RetornaVivo(p->item)==0){
      /*Condiçõa para encerrar a verificação apenas quando o não houver pacinete mortos*/
      achou_morto=1;
      /*Printa no arquivo saída o falecimento do paciente*/
      fprintf(RetornaArquivoSaidaPaciente(p->item), "falecimento");
      /*Retira o paciente morto da lista de pacientes*/
      RetiraLista(lista, RetornaNomePaciente(p->item));
      break;
    }
  }
  } while (p!=NULL&&achou_morto==1);
  

  /*Caso todos os pacientes morram, encerrar a função*/
  if(lista->prim==lista->ult){
    return;
  }

  /*Verfifica as condições dos pacientes e toma as devidas providências*/
  for(p = lista->prim; p!=NULL; p=p->prox){
    if (Caiu(p->item)){
      fprintf(RetornaArquivoSaidaPaciente(p->item), "queda, acionou %s\n", RetornaNomeCuidador(CuidadorMaisProximo(p->item)));
    } else if(Febre(p->item)==2){
      fprintf(RetornaArquivoSaidaPaciente(p->item), "febre alta, acionou %s\n", RetornaNomeCuidador(CuidadorMaisProximo(p->item)));
    } else if (Febre(p->item)==1){
      if (RetornaFebre4x(p->item)==1){
        fprintf(RetornaArquivoSaidaPaciente(p->item), "febre baixa pela quarta vez, acionou %s\n", RetornaNomeCuidador(CuidadorMaisProximo(p->item)));
        ZeraFebreBaixa(p->item);
      } else {
      fprintf(RetornaArquivoSaidaPaciente(p->item), "febre baixa, acionou amigo %s\n", RetornaNomePaciente(AmigoMaisProximo(p->item)));
      AumentaFebreBaixa(p->item);
      }
    } else if (Febre(p->item)==0&&!Caiu(p->item)){
      fprintf(RetornaArquivoSaidaPaciente(p->item), "tudo ok\n");
    }
  }
  }

  
}

Lista * LePacientes(){
  Lista * pacientes = InicLista();
  char todos_os_nomes[200]="\0";
  char * nome;
  /*Le os pacientes no apoio.txt*/
  FILE * apoio = fopen("apoio.txt", "r");
  fscanf(apoio, "%s", todos_os_nomes);
  /*Separa o nome de cada paciente e cria um elemento tpo Paciente **/
  nome = strtok(todos_os_nomes, ";");
  Paciente * paciente = InicializaPaciente(nome);
  InsereListaPacientes(pacientes, paciente);
  while(1){
    nome = strtok(NULL, ";");
    if(nome==NULL){
      break;
    }
    Paciente * paciente = InicializaPaciente(nome);
    InsereListaPacientes(pacientes, paciente);
  }
  /*Le amigos e registra*/
  char amigo1[20]="\0", amigo2[20]="\0";
  while(fscanf(apoio, "\n%[^;]", amigo1)!=EOF){
    fscanf(apoio, ";%[^\n]", amigo2);
    AdicionarAmigo(BuscaPaciente(pacientes, amigo1), BuscaPaciente(pacientes, amigo2));
  }
  fclose(apoio);
  return pacientes;
}

Lista * LeCuidadores(Lista * pacientes){
  Lista * cuidadores = InicLista();
  char todos_os_nomes[50]="\0";
  char * nome;
  /*Le os cuidadores no cuidadores.txt*/
  FILE * cuidadorestxt = fopen("cuidadores.txt", "r");
  fscanf(cuidadorestxt, "%s", todos_os_nomes);
  /*Separa o nome de cada cuidador e cria um elemento tipo Cuidador **/
  nome = strtok(todos_os_nomes, ";");
  Cuidador * cuidador = InicializaCuidador(nome);
  InsereListaCuidador(cuidadores, cuidador);
  while(1){
    nome = strtok(NULL, ";");
    if(nome==NULL){
      break;
    }
    Cuidador * cuidador = InicializaCuidador(nome);
    InsereListaCuidador(cuidadores, cuidador);
  }
  /*Le os pacientes e atribui ao seu cuidador*/
  char paciente[20], nome_cuidadores[100];
  while(fscanf(cuidadorestxt, "\n%[^;]", paciente)!=EOF){
    fscanf(cuidadorestxt, "%[^\n]", nome_cuidadores);
    nome = strtok(nome_cuidadores, ";");
    //Adicionar o cuidador na lista de cuidadores do paciente
    InsereListaCuidador(RetornaCuidadores(BuscaPaciente(pacientes, paciente)), BuscaCuidador(cuidadores, nome));
    while(1){
    nome = strtok(NULL, ";");
    if(nome==NULL){
      break;
    }
    //Adicionar o cuidador na lista de cuidadores do paciente
    InsereListaCuidador(RetornaCuidadores(BuscaPaciente(pacientes, paciente)), BuscaCuidador(cuidadores, nome));
  }
  }
  fclose(cuidadorestxt);
  return cuidadores;
}