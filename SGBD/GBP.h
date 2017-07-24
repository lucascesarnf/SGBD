//
//  GBP.h
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 20/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#ifndef GBP_h
#define GBP_h

#include <stdio.h>
#include "GED.h"
void initGBP();
Pagina *novaPagina();
int liberaPage(int pid, int durty_bit);
int removePage(int pid);
Pagina* getPage(int pid);
int insereNaFila(int index);
void printMemoria();
void printFila();
/*
void initFrame();
int alocaFrame();
int desalocaFrame(int pid);
int PersistePagina(int pid);
int BuscaEspacoLivre();
void contaLivres();
int LRU(int *time, int n);
int PoliticaDeSubstituicao();
*/
#endif //* GBP_h */

