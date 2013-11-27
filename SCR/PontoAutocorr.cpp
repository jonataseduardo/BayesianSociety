#include "Struct.hpp"

double PontoAutocorr( double * Min, int size, int t)
{
    double x = 0 ,y1 = 0 ,y2 = 0 ,tau = 0 ;
    int i;
    for (i = 0; i < size - t; i++) {
        x  += Min[i]*Min[i+t];
        y1 += Min[i];
        y2 += Min[i+t];
    }
    tau = 1.0/(double)i;
    return  tau*( x - tau * y1*y2 );
}
