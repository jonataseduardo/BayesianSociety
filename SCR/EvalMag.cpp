#include <gsl/gsl_statistics.h>

void EvalMag( double * mi,size_t NUM, double * mag, double * vmag)
{

    *mag = gsl_stats_mean(mi, 1,NUM);
    *vmag =gsl_stats_variance(mi,1,NUM);
}
