#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "alinear.h"

void alinear_der(char *str) {

  char *r=str+strlen(str)-1;
  char *i=str+strlen(str)-1;

  if(strlen(str)==0){
  }
  else { 
    if(*r==' '){
      while((*i==' ') && (i>str)){
        i--;
      }
      while(str<=i){
        char temp=*r;
        *r=*i;
        *i=temp;
        i--;
        r--;
      }
    }
  }
}

// Esta implementacion de alineacion_der es invalida porque usa alinear_der.
// Sera invalida aun si satisface el test de eficiencia.
// Es ineficiente porque hara una copia adicional de los caracteres.
// Debe programar una version de alineacion_der que no use alinear_der.
char *alineacion_der(char *str) {
  char *res= malloc(strlen(str)+1);
  char *l1 = res;
  char *r=str+strlen(str)-1;
  char *l=str;


  if(strlen(str)==0){
    *l1= '\0';
    return res;
  }
  while(*r==' '){

    *l1 = *r;
    if(r==l){ // "a  " -> "  a"
      l1++;
      *l1= '\0';
      return res;
    }
    l1++;
    r--;
  }
  while(l<=r){
    *l1=*l;
    l1++;
    l++;
  }
  
  *l1 = '\0';

  return res;
}

