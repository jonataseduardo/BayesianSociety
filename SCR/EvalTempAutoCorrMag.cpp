#include <stdio.h>
#include <math.h>
#include <gsl/gsl_fit.h>
#include "Struct.hpp"
#include "PontoAutocorr.hpp"
#include "EvalTempAutoCorrMag.hpp"

void EvalTempAutoCorrMag( StrMundo * Mundo , double th, int SIZE,
        double *tm, double *tme )
{
    int NUM = Mundo->NUM;
    int burn = NUM*Mundo->MCTime->burn;
    int step = (int)NUM*Mundo->MCTime->step;

    int T = NUM*Mundo->MCTime->coleta;
    if (SIZE > T)
        SIZE=T;


    double ma, mtau, mcaa, mcat, mctt, mchisq;

    double *Temp, * Xerg, *Xmag, xe = 1, xm = 1;
    Xmag = (double *) malloc( SIZE*sizeof(double));
    Temp = (double *) malloc( SIZE*sizeof(double));


    double xm0 = PontoAutocorr( &(Mundo->evolut->mag[burn-1]), T, 0);

    int i = 0, j = 0;
    do{
        xm = PontoAutocorr( &(Mundo->evolut->mag[burn-1]), T, i)/xm0;
        Temp[j] = j*Mundo->MCTime->step;
        Xmag[j] = log(xm);
        //printf("%g %g \n", Temp[j], Xmag[j]);
        //printf("%g %g \n", Temp[j], xm);
        j++;
        i = j*step;
    }while( (j < SIZE) && ((xe >= th) && (xm >= th)) ); 

    gsl_fit_linear(Temp, 1, Xmag, 1, j, &ma, &mtau, &mcaa, &mcat, &mctt, &mchisq);
    
    *tm = -1.0/mtau;

    free(Temp);          
    free(Xmag);          
}
