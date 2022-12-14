#include <stdio.h>
#include <stdlib.h>

#include "calzar.h"

int calzar(Nodo *a, Nodo **ppat) {
  Nodo *p = *ppat;
  if(p==NULL){ // Si el arbol que se apunta *ppat es nulo
    *ppat=a;
    return 1;
  }
  if((a==NULL)) {
    return 0;
  }
  if(a->x != p->x){ // Si el arbol que se almacena en a y en *ppat, ambos apuntan a uno distintos sin hijos
    return 0;
  }
  else {
      return (calzar(a->izq, &(*ppat)->izq))*(calzar(a->der, &(*ppat)->der));
  }
}