//
//  Data.h
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 13/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#ifndef Data_h
#define Data_h

#include <stdio.h>

//################ C O N S T A N T E S#####################################

#define TM_MAX_BLOCOS 100
#define TM_MAX_REGISTROS 100
#define TM_MAX_FRAMES 5

#define PERSIST_GED "initGED.txt"

//################ S T R U C T S ##########################################


//Um registro previamente criado:

typedef struct registro
{
  int rid;
  char nome[100];
  int idade;
} Registro;

//Uma página que contem um Id e um vetor de registros:

typedef struct pagina{
  int pid;
  Registro data[TM_MAX_REGISTROS];
  int diretorio[TM_MAX_REGISTROS];
} Pagina;

//Lista encadeada de páginas:

typedef struct lista_de_paginas{
  Pagina *pg;
  struct lista_de_paginas *prox;
  struct lista_de_paginas *ant;
}ListaDePaginas;

//Um Bloco de "disco":

typedef struct bloco{
  int end;
  Pagina data;
}Bloco;

//Frame da memoria principal:

typedef struct frame{
  Pagina *pag;
  int pin_count;
  int dirty_bit;
}Frame;

//Arquivo:

typedef struct diretorioDePaginas{
  Pagina *endPage;
  int slotsLivres;
}DiretorioDePaginas;

typedef struct arquivo{
  int aid;
  ListaDePaginas *pages;
  DiretorioDePaginas dirt [TM_MAX_BLOCOS];
}Arquivo;

//
#endif /* Data_h */



