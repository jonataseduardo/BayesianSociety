#include "Struct.hpp"
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_blas.h>

void UpdateHistMag(struct StrMundo * Mundo, gsl_vector * issue, gsl_histogram * h)
{
    double x;
    gsl_vector * aux = gsl_vector_alloc(Mundo->DIM);
    for (size_t i = 0; i < Mundo->NUM ; i++) {
        gsl_vector_memcpy( aux, Mundo->agente[i].opinion );
        gsl_blas_ddot( aux,issue , &x);
        gsl_histogram_increment( h , x );
    }
    gsl_vector_free(aux);
}
