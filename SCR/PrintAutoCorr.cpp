#include <stdio.h>
#include <math.h>
#include "Struct.hpp"
#include "PontoAutocorr.hpp"

void PrintAutoCorr( StrMundo * Mundo , double th, int SIZE, int id)
{
    int NUM = Mundo->NUM;
    int burn = NUM*Mundo->MCTime->burn;

    int T = NUM*Mundo->MCTime->coleta;
    int step = (int)NUM*Mundo->MCTime->step;

    double xe = 1, xm = 1;

    FILE * fp;
    char name[100];
    sprintf(name,"Evol_%s_%d.dat", Mundo->name,id);
    fp = fopen(name, "w");

    double xe0 = PontoAutocorr( &(Mundo->evolut->erg[burn-1]), T, 0);
    double xm0 = PontoAutocorr( &(Mundo->evolut->mag[burn-1]), T, 0);

    int i = 0, j = 1;
    do{
        xe = PontoAutocorr( &(Mundo->evolut->erg[burn-1]), T, i)/xe0;
        xm = PontoAutocorr( &(Mundo->evolut->mag[burn-1]), T, i)/xm0;

        fprintf(fp," %g %g %g %g %g\n"
                , j*Mundo->MCTime->step 
                , xe
                , Mundo->evolut->erg[burn-1+i]
                , xm
                , Mundo->evolut->mag[burn-1+i]
               );
        j++;
        i = j*step;
    }while( (j < SIZE) && ((xe >= th) && (xm >= th)) ); 

    fclose(fp);
}
