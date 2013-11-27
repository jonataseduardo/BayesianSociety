#include <stdlib.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include "Struct.hpp"

void EvalAllOverlaps(struct StrMundo * Mundo, gsl_vector * issue, double ** mi )
{
    double x;
    *mi = (double *) malloc((Mundo->NUM)*sizeof(double));
    gsl_vector * aux = gsl_vector_alloc(Mundo->DIM);

    for (size_t i = 0; i < Mundo->NUM ; i++) {
        gsl_vector_memcpy( aux, Mundo->agente[i].opinion );
        gsl_blas_ddot( aux,issue , &x);
        (*mi)[i] = x;
    }
    gsl_vector_free(aux);
}
