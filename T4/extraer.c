#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int n= atoi("25 \n"); // n es 25
// char s[6], d[6];
// sprintf(s, "%-4d\n", n); // imprime en un string, no en un archivo,
//  // %-4d significa mostrar entero en 4 caracteres, alineado a la izquierda,
//  // s es el string "25 \n" de largo 5
// memcpy(d, s, 4); // copia 4 bytes a partir de s en d

int main(int argc, char *argv[]) {

    FILE *f= fopen(argv[1], "r+");

    if(f == NULL){
        perror(argv[1]);
        exit(1);
    }
    else{
        char buf1[6];
        char buf12[13];
        char buf2[18];
        // char buf3[18];
        char name[13];
        char priority_string[7];

        fread(buf1, 5, 1, f);
        int amount=atoi(buf1);

        if(amount==0){
            fprintf(stderr, "%s\n", "error: cola.txt esta vacia");
            exit(1);
        }
        else{
            int priority=1000000;
            int priority_int;

            int counter=0;
            int delete=0;

            while(counter<amount){
                fread(buf2, 17, 1, f);
                memcpy(priority_string, buf2+10, 7);
                priority_int=atoi(priority_string);
                if(priority_int<priority){
                    priority=priority_int;
                    memcpy(name, buf2, 10);
                    delete++;
                }
                counter++;
            }
            
            name[10]='\0';
            printf("%s\n", name);

            // fseek(f, -4-amount*(16+1), SEEK_CUR);
            fseek(f, 0, SEEK_SET);
            
            amount-=1;

            sprintf(buf12, "%-4d\n", amount);
            memcpy(buf1, buf12, 5);
            buf1[5]='\0';

            fputs(buf1, f);

            fseek(f, 4+1+(delete-1)*(16+1), SEEK_SET);

            buf2[17]='\0';
            fputs(buf2, f);

        }    
    }
}