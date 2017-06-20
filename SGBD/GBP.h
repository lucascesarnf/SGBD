//#ifndef GBP_h
#define GBP_h

#include <stdio.h>
#include "Data.h"
#include <stdlib.h>
#include "GED.h"

void initFrame();
int alocaFrame();
int desalocaFrame(int pid);
int PersistePagina(int pid);
int BuscaEspacoLivre();
void contaLivres();
int LRU(int time[], int n);
int PoliticaDeSubstituicao();
