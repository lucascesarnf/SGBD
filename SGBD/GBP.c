//
//  GBP.c
//  SGBD
//
//  Created by Lucas César  Nogueira Fonseca on 20/06/17.
//  Copyright © 2017 Lucas César  Nogueira Fonseca. All rights reserved.
//

#include "GBP.h"

Frame frames[TM_MAX_BLOCOS];
int heapFrame[TM_MAX_BLOCOS];
int numFramesLivres;

void initFrame(){
  numFramesLivres = TM_MAX_BLOCOS;
  for(int i = 0; i <TM_MAX_BLOCOS; i++){
    heapFrame[i] = 0;
  }
}

int alocaFrame(){
  
  if(numFramesLivres>0){
    
    for(int i = 0; i <TM_MAX_BLOCOS; i++){
      
      if(heapFrame[i]==0){
        Pagina *p = alocaPagina();
        if(p != NULL){
          heapFrame[i] = p->pid;
          frames[i].pag = p;
          return 1;
        }
        else{
          return 0;
        }
      }
    }
  }
  return -1;
}

int desalocaFrame(int pid){
  if(heapFrame[pid]==0){
    return -1;
    
  }else{
    Pagina *pag = frames[pid].pag;
    int t = desalocaPagina(pag->pid);
    if(t == 1){
      heapFrame[pid]=0;
      contaLivres();
      return 1;
    }else{
      return 0;
    }
  }
}

int PersistePagina(int pid){
  Pagina *pag = frames[pid].pag;
  int aux = frames[pid].dirty_bit;
  if(aux == 1){
    return escritaPagina(pag);
  }
  else{
    return -1;
  }
}

int BuscaEspacoLivre(){
  if(numFramesLivres>0){
    
    for(int i =0;i<TM_MAX_BLOCOS;i++){
      
      if(heapFrame[i]==0){
        return i;
      }
    }
    
  }
  return -1;
  //return PoliticaDeSubstituicao();
}

void contaLivres(){
  numFramesLivres = 0;
  for(int i = 0;i<TM_MAX_BLOCOS;i++){
    if(heapFrame[i]==0){
      numFramesLivres ++;
    }
  }
}

int LRU(int *time, int n){
  
  int minimum = time[0];
  int  pos = 0;
  
  for(int i = 1; i < n; i++){
    if(time[i] < minimum){
      minimum = time[i];
      pos = i;
    }
  }
  
  return pos;
}


int PoliticaDeSubstituicao()
{
  int no_of_frames = TM_MAX_BLOCOS , no_of_pages = TM_MAX_BLOCOS, frames[10], pages[30], count = 0, time[10], flag1, flag2, i, j, pos = 0, faults = 0;
  
  for(i = 0; i < no_of_frames; ++i){
    frames[i] = -1;
  }
  
  for(i = 0; i < no_of_pages; ++i){
    flag1 = flag2 = 0;
    
    for(j = 0; j < no_of_frames; ++j){
      if(frames[j] == pages[i]){
        count++;
        time[j] = count;
        flag1 = flag2 = 1;
        break;
      }
    }
    
    if(flag1 == 0){
      for(j = 0; j < no_of_frames; ++j){
        if(frames[j] == -1){
          count++;
          faults++;
          frames[j] = pages[i];
          time[j] = count;
          flag2 = 1;
          break;
        }
      }
    }
    
    if(flag2 == 0){
      pos = LRU(time, no_of_frames);
      count++;
      faults++;
      frames[pos] = pages[i];
      time[pos] = count;
    }
  }
  return pos;
}
