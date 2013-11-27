#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>

void  NormalizeGslVector(gsl_vector * aux )
{
    double x = gsl_blas_dnrm2 (aux);
    gsl_vector_scale(aux,1.0/x);
}
