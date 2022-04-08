#include <stdio.h>
#include <string.h>
#include "paciente.h"
#include "lista.h"
#include "cuidador.h"

int main(void) {
  Lista * pacientes = LePacientes();
  Lista * cuidadores = LeCuidadores(pacientes);
  Leitura(pacientes, cuidadores);
  DestroiListaPacientes(pacientes);
  DestroiListaCuidadores(cuidadores);
  printf("EDCare rodado com exito!\nNenhum erro encontrado...\n");
  /*As funções de destruição de lista já liberão os pacientes, cuidadores, bem como nomes e fecham arquivos*/
  return 0;
}