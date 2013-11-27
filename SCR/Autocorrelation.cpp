#include "Struct.hpp"

void Autocorrelation( double * Min, int size, double ** Mout)
{
    double x,y1,y2,tau;
    int i, t;
    *Mout = (double *)malloc( (size_t)size * sizeof(double) );
    for (t = 0; t < size; t++) {
        x  = 0.0;
        y1 = 0.0;
        y2 = 0.0;
        for (i = 0; i < size - t; i++) {
            x  += Min[i]*Min[i+t];
            y1 += Min[i];
            y2 += Min[i+t];
        }
        tau = 1.0/(double)i;
        //printf("%d %d %.2g %.2g\n", t, i, tau, tau*(x -tau*y1*y2));
        (*Mout)[t] = tau*( x - tau * y1*y2 );
    }
}
