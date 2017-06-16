//
//  GED.h
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 13/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#ifndef GED_h
#define GED_h

#include <stdio.h>
#include "Data.h"
#include <stdlib.h>

int initGED();
Pagina *alocaPagina();
int desalocaPagina(int pid);
Pagina *leituraDePagina(int pid);
int escritaPagina(Pagina *p);
int closeGED();
void contaLivres();
void printHeapBlocos();
//#####################
void TesteEscreveArquivo();
void TesteLeArquivo();


#endif /* GED_h */
