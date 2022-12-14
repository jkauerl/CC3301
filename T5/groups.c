#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "groups.h"

int groups(unsigned int x) {
  // Programe aca la funcion groups
  unsigned mask = x<<1;
  int counter=0;

  while(x){
    if((x&1)==1 && (mask&1)==0 ){
      counter++;
    }
    x>>=1;
    mask>>=1;
  }
  return counter;
}