#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#include "pss.h"

// Defina aca los tipos, variables globales y funciones que necesite
// ...

typedef struct {
  char* name;
  long long date;
} File;

Queue *q;

int cmpDate(void *ptr, int i, int j) {
  File **f = ptr;
  return f[j]->date - f[i]->date; 
}

void masrecientes(char *nom) {
  struct stat st_nom;
  int rc;
  rc= stat(nom, &st_nom);

  if (rc!=0) {
    printf("%s no existe\n", nom);
    exit(0);
  }

  if (S_ISREG(st_nom.st_mode)) {
    // Es un archivo regular
    
    char *nom_arch= strdup(nom);

    long long mdate = st_nom.st_mtime;

    File *file = malloc(sizeof(File));

    file->name = nom_arch;
    file->date = mdate;

    put(q, file);
  }

  else if (S_ISDIR(st_nom.st_mode)) {
    // Es un directorio
    DIR *dir = opendir(nom);
    if (dir == NULL) {
      perror(nom);
      exit(1);
    }
    for (struct dirent *entry = readdir(dir);
         entry != NULL;
         entry = readdir(dir)) {
      if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0) {
        continue;
      }
      char *nom_arch= malloc(strlen(nom)+strlen(entry->d_name)+2);
      strcpy(nom_arch, nom);
      strcat(nom_arch, "/");
      strcat(nom_arch, entry->d_name);
      masrecientes(nom_arch);
      free(nom_arch);
    }
    closedir(dir);
  }
  else {
    // Podria ser un dispositivo, un link simbolico, etc.
    fprintf(stderr, "Archivo %s es de tipo desconocido\n", nom);
    exit(1);
  }
}

int main(int argc, char *argv[]) {

  q = makeQueue();

  masrecientes(argv[1]);
  int length = queueLength(q);
  File *File[length];
  for(int i=0; i<length; i++){
    File[i] = get(q);
  }

  int n = atoi(argv[2]);

  sortPtrArray(File, 0, length-1, cmpDate);
  for(int i=0; i<n; i++){
    printf("%s\n", File[i]->name);
  }
  for(int i=0; i<length; i++){
    free(File[i]->name);
    free(File[i]);
  }
  destroyQueue(q);
  return 0;
}
