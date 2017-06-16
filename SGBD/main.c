//
//  main.c
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 13/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

/*A estrutura do projeto guarta todas as Structs e constantes no arquivo Data.h, assim dodos os dados necessários para o funcionamento do programa devem ficar lá, e para utiliza-los é só dar um #include "Data.h"*/

#include <stdio.h>
#include "Data.h"
#include "GED.h"
int main(int argc, char *argv[]){
  // insert code here...
  /*
  Registro jao;
  Registro *reg = &jao;
  (*reg).idade = 18;
  (*reg).rid = 1;
  strcpy((*reg).nome, "joao da silva");
  
  printf("ID:(%d),%s, %d\n",(*reg).rid,(*reg).nome, (*reg).idade);
  */
  initGED();
  Pagina *p1,*p2,*p3,*p4;
  p1 = alocaPagina();
  if(p1!=NULL){
    printf("\nP1:%d\n",p1->pid);
  }
  p2 = alocaPagina();
  if(p2!=NULL){
    printf("\nP2:%d\n",p2->pid);
  }
  p3 = alocaPagina();
  if(p3!=NULL){
    printf("\nP3:%d\n",p3->pid);
  }
  p4 = alocaPagina();
  if(p4!=NULL){
    printf("\nP4:%d\n",p4->pid);
  }
  
  printHeapBlocos();
  printf("\n##[%d]##\n",desalocaPagina(p2->pid));
  printHeapBlocos();
  printf("\n##[%d]##\n",desalocaPagina(p2->pid));
  printHeapBlocos();
  printf("\n##[%d]##\n",desalocaPagina(p3->pid));
  printHeapBlocos();
  
  closeGED();
  
  return 0;
}
