//
//  GA.c
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 13/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#include "GA.h"
//criar uma matriz 3x100 sendo os valores de cada matriz espaco livre numero da pagina
// conteudo da pagina


// principais funcoes cria/deleta/busca/insere arquivo todas serao feitas pelo id da pagina
// definir qual o tamanho total dos dados da pagina

Arquivo *data;
int heapArquivos[TM_MAX_BLOCOS];

//inicializa o GA
void initGA(){
  data = (Arquivo*)(malloc(TM_MAX_BLOCOS*sizeof(Arquivo)));
  for(int i = 0; i <TM_MAX_BLOCOS; i++){
    heapArquivos[i] = 0;
  }
}

// Cria Arquivo
Arquivo *criaArquivo(){
  Arquivo a;
  int local_livre=-1;
  ListaDePaginas *p = NULL;
  a.pages = p;
  for(int i = 0; i <TM_MAX_BLOCOS; i++){
    a.dirt[i].endPage = NULL;
    a.dirt[i].slotsLivres = TM_MAX_REGISTROS;
  }
  for(int i = 0; i <TM_MAX_BLOCOS; i++){
    if(heapArquivos[i] == 0){
      a.aid = i;
      data[i] = a;
      local_livre = i;
      heapArquivos[i] = 1;
      return &data[local_livre];
    }
  }
  if(local_livre != -1){
    return &data[local_livre];
  }else{
    return NULL;
  }
}

// Deleta arquivo, retorna -1 para página inesistente, 1 sucesso, 0 fracasso:

int deletaArquivo(int aid){
  if(data[aid].aid == aid){
    heapArquivos[aid] = 0;
    //Temos que deletar as páginas do arquivo?? Se sim :
    /*
     struct lista_de_paginas *arq = data[aid].pages;
     struct lista_de_paginas *aux = NULL;
     while(arq != NULL){
     if(arq->prox != NULL){
     aux = arq;
     }
     int status = desalocaPagina(arq->pg->pid);
     arq = aux;
     if(status == -1){
     return -1;
     }*/
    return 1;
  }
  return 0;
}


Arquivo *buscaArquivo(int aid){
  if(heapArquivos[aid]!= 0){
    return &data[aid];
  }
  return NULL;
}
//Insere Registro em arquivo, retorna -1 para página inesistente, 1 sucesso, 0 fracasso:
int insereRegistro(int aid , Registro r){
  
  if(heapArquivos[aid]==1){
    for(int i = 0;i<TM_MAX_BLOCOS;i++){
      if(data[aid].dirt[i].slotsLivres > 0){
        if(data[aid].dirt[i].endPage == NULL){
          Pagina *pg = alocaPagina();
          if(pg != NULL){
            data[aid].dirt[i].endPage = pg;
            for(int j = 0; j< TM_MAX_REGISTROS; j++){
              if(data[aid].dirt[i].endPage->diretorio[j]==0){
                data[aid].dirt[i].endPage->data[j] = r;
                data[aid].dirt[i].endPage->diretorio[j] = 1;
                escritaPagina(data[aid].dirt[i].endPage);
                return 1;
              }
            }
          }
        }else{
          for(int j = 0; j< TM_MAX_REGISTROS; j++){
            if(data[aid].dirt[i].endPage->diretorio[j]==0){
              data[aid].dirt[i].endPage->data[j] = r;
              data[aid].dirt[i].endPage->diretorio[j] = 1;
              escritaPagina(data[aid].dirt[i].endPage);
              return 1;
            }
          }
        }
      }
    }
    return 0;
  }
  return -1;
}

//Remove Registro em arquivo, retorna -1 para página inesistente, 1 sucesso, 0 fracasso:
int removeRegistro(int aid , int rid){
  if(heapArquivos[aid]==1){
    for(int j = 0; j< TM_MAX_BLOCOS; j ++){
      for(int i = 0; i< TM_MAX_REGISTROS; i++){
        if(data[aid].dirt[j].endPage != NULL){
          if(data[aid].dirt[j].endPage->data[i].rid == rid){
            data[aid].dirt[j].endPage->diretorio[i] = 0;
            return 1;
          }
        }
      }
    }
    return 0;
  }
  return -1;
}

//Busca arquivo em páginas
Pagina *buscaRegistro(int rid, int aid){
  if(heapArquivos[aid]==1){
    for(int j = 0; j< TM_MAX_BLOCOS; j ++){
      for(int i = 0; i< TM_MAX_REGISTROS; i++){
        if(data[aid].dirt[j].endPage != NULL){
          if(data[aid].dirt[j].endPage->data[i].rid == rid){
            return data[aid].dirt[j].endPage;
          }
        }
      }
    }
    return NULL;
  }
  return NULL;
}




