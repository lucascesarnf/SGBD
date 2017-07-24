//
//  main.c
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 13/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

/*
 
 A estrutura do projeto guarta todas as Structs e constantes no arquivo Data.h,
 assim dodos os dados necessários para o funcionamento do programa devem ficar lá, 
 e para utiliza-los é só dar um #include "Data.h"
 
 */

#include <stdio.h>
#include "Data.h"
#include "GED.h"
#include "GA.h"
#include "GBP.h"
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
  initGA();
  initGBP();
  /*
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
  printf("\n\nBlocos em uso:%d\n\n",blocosEmUso());
  */
  
  //Cria Arquivos:
  Arquivo arq1 = *criaArquivo();
  printf("\nId arq:%d\n",arq1.aid);
  Arquivo arq2 = *criaArquivo();
  printf("\nId arq:%d\n",arq2.aid);
  
  //Registro1:
    Registro r1;
    r1.idade = 18;
    strcpy(r1.nome,"Lucas César");
    r1.rid = 0;
  //Registro2:
    Registro r2;
    r2.idade = 19;
    strcpy(r2.nome,"Fulaninho de Tal");
    r2.rid = 1;
  //Registro3:
    Registro r3;
    r3.idade = 18;
    strcpy(r3.nome,"Joãozinho");
    r3.rid = 2;
  //Registro4:
    Registro r4;
    r4.idade = 19;
    strcpy(r4.nome,"Branquinho");
    r4.rid = 3;
  
  Pagina *p1 = novaPagina();
  printMemoria();
  Pagina *p2 = novaPagina();
  printMemoria();
  Pagina *p3 = novaPagina();
  printMemoria();
  Pagina *p4 = novaPagina();
  printMemoria();
  Pagina *p5 = novaPagina();
  printMemoria();
  printFila();
  Pagina *p6 = novaPagina();
  printMemoria();
  printFila();
  //sequencial flooding:
  Pagina *p7 = novaPagina();
  printMemoria();
  printFila();
  
  
  Pagina *p8 = getPage(1);
  printMemoria();
  printFila();
  

  //Insere no Arquivo 1:
  printf("\n##[%d]##\n",insereRegistro(arq1.aid, r1));
  printf("\n##[%d]##\n",insereRegistro(arq1.aid, r2));
  printf("\n##[%d]##\n",insereRegistro(arq1.aid, r3));
  printf("\n##[%d]##\n",insereRegistro(arq1.aid, r4));
  //Insere no Arquivo 2:
  printf("\n##[%d]##\n",insereRegistro(arq2.aid, r3));
  printf("\n##[%d]##\n",insereRegistro(arq2.aid, r4));
  
  printPaginasNaMemoria();
  //Remove no Arquivo 1:
  printf("\n##[%d]##\n",removeRegistro(arq1.aid, r3.rid));
  printf("\n##[%d]##\n",removeRegistro(arq1.aid, 7));
  
  printPaginasNaMemoria();
 // printHeapBlocos();
   

  closeGED();
  
  
  return 0;
}
