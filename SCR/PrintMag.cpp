#include <stdio.h>
#include <gsl/gsl_blas.h>
#include "Struct.hpp"

void PrintMag(StrMundo * Mundo )
{
    double x;
    int NUM = Mundo->NUM;
    FILE * fp;
    char name[100];
    sprintf(name,"MAG_%s.dat",Mundo->name);
    fp = fopen(name, "a+");
    for (int i = 0; i < NUM; i++) {
        gsl_blas_ddot( Mundo->agente[i].opinion , Mundo->issues->zeit , &x);
        //printf("%d %g /n",i, x);
        fprintf(fp, "%g \n", x);
    }
    fclose(fp);
}
