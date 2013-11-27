#include <gsl/gsl_rng.h>
#include <time.h>
#include <unistd.h>

void StartGslRngSeed(gsl_rng ** r)
{
    const gsl_rng_type *T;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    *r = gsl_rng_alloc(T);
    long seed = time (NULL) * getpid();
    //seed = 13188839657852;
    gsl_rng_set(*r,seed);
}
