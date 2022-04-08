#include "paciente.h"
#include "cuidador.h"
#include <stdlib.h>
#include <math.h>

/*Tipo opaco lista genérica*/
typedef struct lista Lista;

/*Aloca espaço para a lista genérica*/
Lista * InicLista();

/*Insere um paciente em uma lista genérica*/
void InsereListaPacientes(Lista * lista, Paciente * pessoa);

/*Insere um cudiador em uma lista genérica*/
void InsereListaCuidador(Lista * lista, Cuidador * cuidador);

/*Imprime uma alista genérica de pacinetes*/
void ImprimeListaPacientes(Lista* lista);

/*Imprime uma lista genérica de cuidadores*/
void ImprimeListaCuidadores(Lista* lista);

/*Imprime uma lista genérica de pacientes, juntamente com sua lista genérica de cudiadores*/
void ImprimePacientesECuidadores (Lista * pacientes);

/*Retira um paciente de uma lista*/
Paciente * RetiraLista(Lista * lista, char * nome);

/*Libera a memória alocada para a lista de pacientes*/
void DestroiListaPacientes(Lista* lista);

/*Libera a memória alocada para a lista de cuidadores*/
void DestroiListaCuidadores(Lista* lista);

/*Destroi lista de amigos do paciente*/
void DestroiListaDeAmigos(Paciente * paciente);

/*Destroi lista decuidadores do paciente*/
void DestroiListaDeCuidadores(Paciente * paciente);

/*Devolve um ponteiro para um paciente contido em uma lista*/
void * BuscaPaciente (Lista * lista, char * chave);

/*Devolve o ponteiro para um cuidador contido em uma lista*/
void * BuscaCuidador (Lista * lista, char * chave);

/*Executa a leitura e atualização de todos os arquivos dos pacientes e cuidadores*/
void Leitura(Lista * lista, Lista * cuidadores);

/*Retorna um ponteiro para o amigo mais próximo do paciente passado como parâmetro*/
Paciente * AmigoMaisProximo(Paciente * paciente);

/*Retorna o cuidador mais próximo do paciente passado como parâmetro*/
Cuidador * CuidadorMaisProximo(Paciente * paciente);

/*Le os pacientes existentes no apoio.txt e estabelece a rede de amizades*/
Lista * LePacientes();

/*Le os cuidadores existentes em cuidadores.txt e estabeleca a rede de cuidado*/
Lista * LeCuidadores(Lista * pacientes);

/*Retorna a distância entre dois pacientes*/
double CoeficienteDistanciaPacientes(Paciente * paciente1, Paciente * paciente2);

/*Retorna a distância entre um paciente e um cuidador*/
double CoeficienteDistanciaCuidador(Paciente * paciente, Cuidador * cuidador);