#include <gsl/gsl_histogram.h>

void NormalizaGSLHistograma( gsl_histogram * h )
{
    double A = 0.0, lower ,upper;
    for (size_t i = 0; i < h->n; i++) {
        gsl_histogram_get_range( h, i, &lower, &upper);
        A += gsl_histogram_get(h,i)*(upper -lower);
    }
    gsl_histogram_scale( h, 1.0/A/(double)h->n );
}
