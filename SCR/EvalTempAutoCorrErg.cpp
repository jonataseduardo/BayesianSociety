#include <stdio.h>
#include <math.h>
#include <gsl/gsl_fit.h>
#include "Struct.hpp"
#include "PontoAutocorr.hpp"
#include "EvalTempAutoCorrErg.hpp"

void EvalTempAutoCorrErg( StrMundo * Mundo , double th, int SIZE,
        double *te, double *tee )
{
    int NUM = Mundo->NUM;
    int burn = NUM*Mundo->MCTime->burn;
    int step = (int)NUM*Mundo->MCTime->step;

    int T = NUM*Mundo->MCTime->coleta;
    if (SIZE > T)
        SIZE=T;


    double ea, etau, ecaa, ecat, ectt, echisq;

    double *Temp, * Xerg, *Xmag, xe = 1, xm = 1;
    Xerg = (double *) malloc( SIZE*sizeof(double));
    Temp = (double *) malloc( SIZE*sizeof(double));


    double xe0 = PontoAutocorr( &(Mundo->evolut->erg[burn-1]), T, 0);

    int i = 0, j = 0;
    do{
        xe = PontoAutocorr( &(Mundo->evolut->erg[burn-1]), T, i)/xe0;
        Temp[j] = j*Mundo->MCTime->step;
        Xerg[j] = log(xe);
        //printf("%g %g \n", Temp[j], Xerg[j]);
        //printf("%g %g \n", Temp[j], xe );
        j++;
        i = j*step;
    }while( (j < SIZE) && ((xe >= th) && (xm >= th)) ); 

    gsl_fit_linear(Temp, 1, Xerg, 1, j, &ea, &etau, &ecaa, &ecat, &ectt, &echisq);
    
    *te = -1.0/etau;

    free(Temp);          
    free(Xerg);          
}
