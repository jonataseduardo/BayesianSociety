#include <stdio.h>
#include "../SCR/Struct.hpp"

void GetSamplesEvolut( StrMundo * Mundo,  double stride, StrOnline * samples )
{
    int NUM = Mundo->NUM;
    int burn = NUM*Mundo->MCTime->burn;
    int dt, T = NUM*Mundo->MCTime->coleta; 
    if (stride > 1.0)
        dt = (int)(NUM*stride);
    else
        dt = NUM;

    int i = 0 ,a = 0 ;
    int j = samples->tempo;
    for (i = 0; i < T; i += dt) {
        samples->mag[ j]=Mundo->evolut->mag[burn-1+i];
        samples->erg[ j]=Mundo->evolut->erg[burn-1+i];

        for (int k = i; k < i+ dt; k++) {
            a = 0;
            if ( Mundo->evolut->acept[burn-1+k] > 0.1)  a++;
        }
        samples->acept[j] = 1.0 - a/((double)dt);
        //printf("%d %d %g %g % g\n", burn -1 + i , j,
                //samples->mag[j],
                //samples->erg[j],
                //samples->acept[j]);
        j++;
    }
    samples->tempo = j;
   
}
