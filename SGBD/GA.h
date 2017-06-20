//
//  GA.h
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 13/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#ifndef GA_h
#define GA_h

#include <stdio.h>

#include "Data.h"
#include "GED.h"

void initGA();
Arquivo *criaArquivo();
int deletaArquivo(int aid);
Arquivo *buscaArquivo(int aid);
int insereRegistro(int aid , Registro r);
int removeRegistro(int aid ,int pid, int rid);
Pagina *buscaRegistro(int rid, int aid);

#endif /* GA_h */
