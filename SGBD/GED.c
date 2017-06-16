//
//  GED.c
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 13/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

/* 
 
 O Gerenciador de espaço em disco tem tamanho fixo de 100 blocos setado na variável TM_MAX_BLOCOS,
 assim o tamanho do nosso disco é dado pela variável TM_MAX_BLOCOS. Para cada bloco o GED aloca 
 um arquivo e guarda os dados do bloco neste arquivo, para emular o acesso aos pratos,
 cilindros e trilhas temos um heap de blocos heapBlocos[TM_MAX_BLOCOS], 
 assim conseguimos abstrair esses detalhes e trabalhar com os blocos como se fossem indices.
 Assim o GA e o GBP trabalham apenas com as estruturas de dados levantadas pra
 eles sem se preocupar como estes dados são guardados na memória.
 
 */

#include "GED.h"
#include <string.h>
Bloco blocos[TM_MAX_BLOCOS];
int heapBlocos[TM_MAX_BLOCOS];
int numBlocosLivres;

//Inicia o GED(Faz o boot do SO KKKKKKK):

int initGED(){
  
  FILE *file = fopen(PERSIST_GED,"rb");
  if (file == NULL){
    numBlocosLivres = TM_MAX_BLOCOS;
    for(int i=0;i<TM_MAX_BLOCOS; i++){
      heapBlocos[i] = 0;
    }
    return 0;
  }else{
    fread(heapBlocos, sizeof(int), sizeof(heapBlocos), file);
    printHeapBlocos();
    contaLivres();
    fclose(file);
    return 1;
  }
}

//Aloca página no "Disco"(arquivo):

Pagina *alocaPagina(){
  
  if(numBlocosLivres>0){
    
    for(int i =0;i<TM_MAX_BLOCOS;i++){
      
      if(heapBlocos[i]==0){
        Bloco b;
        FILE *file;
        char file_name[20];
        sprintf(file_name, "bloco%d.txt",i);
        file = fopen(file_name,"wb");
        
        if (file == NULL){
          printf("Não foi possível alocar página");
          return NULL;
        }else{
          fwrite(&b, sizeof(Bloco), 1, file);
          fclose(file);
          heapBlocos[i] = 1;
          b.end = i;
          b.data.pid = i;
          blocos[i] = b;
          contaLivres();
          return &blocos[i].data;
        }
        break;
      }
      
    }
    
  }
  return NULL;
}

//Desaloca página do "Disco"(arquivo), retorna -1 para página inesistente, 1 sucesso, 0 fracasso:

int desalocaPagina(int pid){
  if(heapBlocos[pid]==0){
    //Página não existe na memória
    return -1;
    
  }else{
    char file_name[20];
    sprintf(file_name, "bloco%d.txt",pid);
    int t = remove(file_name);
    if(t == 0){
      printf("\nRemoveu\n");
      heapBlocos[pid]=0;
      contaLivres();
      return 1;
    }else{
      printf("\nNão Removeu\n");
      return 0;
    }
  }
}
//Lê Página na memória
Pagina *leituraDePagina(int pid){
  if(heapBlocos[pid]==1){
    Bloco b;
    FILE *file;
    char file_name[20];
    sprintf(file_name, "bloco%d.txt",pid);
    file = fopen(file_name,"rb");
    if (file == NULL){
      printf("Não foi possível abrir o arquivo");
      return NULL;
    }else{
      fread(&b,sizeof(Bloco),1,file);
      blocos[pid]=b;
      return &b.data;
    }
  }else{
    return NULL;
  }
}
//Sobrescreve página na memôria, retorna -1 para página inesistente, 1 sucesso, 0 fracasso::
int escritaPagina(Pagina *p){
  if(heapBlocos[p->pid]==0){
    return -1;
  }else{
    Bloco b;
    b.end = p->pid;
    b.data = *(p);
    FILE *file;
    char file_name[20];
    sprintf(file_name, "bloco%d.txt",b.end);
    file = fopen(file_name,"wb");
    if (file == NULL){
      printf("Não foi possível alocar página");
      return 0;
    }else{
      fwrite(&b, sizeof(Bloco), 1, file);
      fclose(file);
      return 1;
    }
  }
}

//Desliga nosso GED e persiste o estado consistente:

int closeGED(){
  printHeapBlocos();
  FILE * file = fopen(PERSIST_GED,"wb");
  if (file == NULL){
    printf("Não foi persistir o GED");
    return 0;
  }else{
    fwrite(heapBlocos, sizeof(int), sizeof(heapBlocos), file);
    fclose(file);
    return 1;
  }
}

//Busca espaço livre no disco:

int espacoLivre(){
  if(numBlocosLivres>0){
    
    for(int i =0;i<TM_MAX_BLOCOS;i++){
      
      if(heapBlocos[i]==0){
        return i;
      }
    }
    
  }
  return -1;
}

//################ F U N C O E S   A U X I L I A R E S #########################################
void contaLivres(){
  numBlocosLivres = 0;
  for(int i = 0;i<TM_MAX_BLOCOS;i++){
    if(heapBlocos[i]==0){
      numBlocosLivres ++;
    }
  }
}
void printHeapBlocos(){
  printf("\n");
  for(int i = 0;i<TM_MAX_BLOCOS; i++){
    if(i%10 == 0){
      printf("\n");
    }
    printf("%d|",heapBlocos[i]);
  }
  printf("\n");
}
//########### E X E M P L O S  DE  A R Q U I V O S ############################################
void TesteEscreveArquivo(){
  Pagina p;
  p.data[0].idade=21;
  strcpy(p.data[0].nome,"Lucas César");
  p.data[0].rid=13091995;
  p.pid = 1;
  Bloco b;
  b.end = 1;
  b.data = p;
  
  FILE *file;
  char file_name[20];
  sprintf(file_name, "bloco%d.txt", b.end);
  //printf("\n\n%s\n\n",file_name);
  file = fopen(file_name,"wb");
  if (file == NULL){
    printf("Não foi possível abrir o arquivo");
  }else{
    fwrite(&b, sizeof(Bloco), 1, file);
    fclose(file);
  }
  
  
  
}

void TesteLeArquivo(){
  Pagina p;
  Bloco b;
  FILE *file;
  char file_name[20];
  sprintf(file_name, "bloco%d.txt",1);
  file = fopen(file_name,"rb");
  if (file == NULL){
    printf("Não foi possível abrir o arquivo");
  }else{
    fread(&b,sizeof(Bloco),1,file);
    p = b.data;
    printf("\n\n[%d]%s->%d\n\n",p.data[0].rid,p.data[0].nome,p.data[0].idade);
  }
}
