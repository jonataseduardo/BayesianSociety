#include <gsl/gsl_vector.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "NormalizeGslVector.hpp"

void SampleNormedRndVecWBias(gsl_vector* opinion, double x, gsl_rng * r)
{
    for (size_t i = 0; i < opinion->size ; i++)
        gsl_vector_set(opinion,i, x + gsl_ran_ugaussian(r) );
    NormalizeGslVector(opinion);
}

