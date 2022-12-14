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

    FILE *f = fopen(argv[1], "r+");

    if(f == NULL){
        perror(argv[1]);
        exit(1);
    }
    else{
        char buf1[5];
        char buf2[18];
        char buf3[11];
        char name[11];
        char priority_string[7];

        fread(buf1, 5, 1, f);
        int amount=atoi(buf1);

        if(amount==0){
            perror("error.txt");
            exit(1);
        }
        else{
            
            int priority=1000000;
            int priority_int;

            int counter=0;
            while(counter<amount){
                fread(buf2, 17, 1, f);
                memcpy(priority_string, buf2+9, 7);
                priority_int=atoi(priority_string);
                if(priority_int<priority){
                    priority=priority_int;
                    memcpy(name, buf2, 10);
                }
                counter++;
            }
            buf2[17]='\0';
            name[10]='\0';

            printf("%s\n", name);

            fseek(f, 0, SEEK_SET);

            /* char c=fgetc(f);

            printf("%c\n", c); */

            // fseek(f, -4-(amount)*(16+1), SEEK_CUR);
            
            amount-=1;

            fputs("   ", f);

            fseek(f, -3, SEEK_CUR);
            sprintf(buf1, "%-4d", amount);


            /* printf("%d", strlen(buf1));
            printf("%d", sprintf(buf1, "%-4d", amount)); */
            fputs(buf1, f);


            // printf("%d", 1);

            fseek(f, 1, SEEK_CUR);
            
            buf3[10]='\0';

            fgets(buf3, 11, f);

            // printf("%s", buf3);
            
            // printf("%d\n", strlen(buf3));

            


            fseek(f, 12, SEEK_CUR);

            
            int rest=1;
            while(strcmp(buf3, name) != 0){

                // fseek(f, -1, SEEK_CUR);
                fseek(f, 12-rest, SEEK_CUR);
                fgets(buf3, 11, f);
                rest++;
            }

            fseek(f, -6, SEEK_CUR);
            
            fputs("          ", f);

            fseek(f, -10, SEEK_CUR);

            fwrite(buf2, 15, 1, f);
        }
    }
}