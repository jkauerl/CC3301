#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

    char test1[] = "prueba 1";

    printf("%d\n", strlen(test1));


    char test2[5];

    test2[0]='a';

    printf("%d\n", strlen(test2));
    printf("%s\n", test2);

    char test3[4] = "p3";

    test3[2] = '\n';
    test3[3] = '\0';

    printf("%d\n", strlen(test3));
    printf("%s", test3);

    printf("%s", test2);

}