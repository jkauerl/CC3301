#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "integral.h"

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
    // ... programe aca la solucion de su tarea ...
    // esto no cumple el speed up solicitado

    int pids[p];
    int fds[p][2];

    double h=(xf-xi)/p;
    for(int i=0; i<p; i++){
        pipe(fds[i]);
        pids[i] = fork();

        if(pids[i] == 0){
            close(fds[i][0]);
            double lower_bound=xi+h*i;
            double upper_bound=xi+h*(i+1);
            double res=integral(f, ptr, lower_bound, upper_bound, n/p);
            write(fds[i][1], &res, sizeof(double));
            exit(0);
        }
        else{
            close(fds[i][1]);
        }
    }

    double res=0;
    for(int i=0; i<p; i++){
        double res_child;
        read(fds[i][0], &res_child, sizeof(double));
        close(fds[i][0]);
        waitpid(pids[i], NULL, 0);
        if(res_child != 0){
            res+=res_child;
        }
    }
    return res;
}

