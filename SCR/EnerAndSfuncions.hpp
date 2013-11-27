#include <gsl/gsl_sf_psi.h>
#include <gsl/gsl_sf_gamma.h>

double Sign (double x )
{ return (x >= 0)?1.0:-1.0; }

double RVsoci (double h1, double sigma2, double d )
{return (h1*sigma2 >= 0)? d:1; }

double ErgCR ( double delta, double h1, double h2 )
{ return 0.5*h1*h2*( -(1+delta) +  (1-delta)*Sign(h1*h2) ); }

double ErgOptN ( double lambda, double h1, double h2){
    double B = 0.707106781, A = 0.693147181; // B = 1/sqrt(2), A = ln(2)
    double x = h1*Sign(h2)/lambda;
    return -lambda*( -A + log(erfc(-B*x)) );
}

double ErgOptN1 ( double lambda, double h1, double h2){
    double B = 0.707106781, A = 0.693147181; // B = 1/sqrt(2), A = ln(2)
    double x = h1*Sign(h2)/lambda;
    return -lambda*lambda*( -A + log(erfc(-B*x)) );
}

double KLbetas(double a1, double b1, double a2, double b2){
    return gsl_sf_lnbeta(a2,b2) - gsl_sf_lnbeta(a1,b1)
            -(a2 - a1)*gsl_sf_psi(a1)
            -(b2 - b1)*gsl_sf_psi(b1)
            +(a2 - a1 + b2 - b1)*gsl_sf_psi(a1 + b1);
}
