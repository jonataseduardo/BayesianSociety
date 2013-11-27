#include <gsl/gsl_rng.h>
#include "Struct.hpp"
#include "SampleNormedRndVecWBias.hpp"
#include "ErgViz.hpp"
#include "EvalAllOverlaps.hpp"
#include "EvalEMTotalOffline.hpp"

void MetropolizOnline(struct StrMundo * Mundo, int node,  double (*Erg)(double, double,double), gsl_rng * r)
{
    int tempo = Mundo->evolut->tempo;
    Mundo->evolut->tempo = tempo + 1;
    double hi, hf, Ei, Ef;
    int ok = 1;
    ErgViz( Mundo , node, Erg, &hi, &Ei);

    gsl_vector * OpNew = gsl_vector_alloc( Mundo->DIM );
    SampleNormedRndVecWBias( OpNew, 0.0, r );
    gsl_vector_swap( OpNew , Mundo->agente[node].opinion );
    ErgViz( Mundo , node, Erg, &hf, &Ef);

    if ( Ef <= Ei ) {
        Mundo->evolut->acept[tempo] = -1.0;
    }else{
        if( gsl_rng_uniform(r) <= exp( (Mundo->beta)*( Ei - Ef) ) ) {
            Mundo->evolut->acept[tempo] = 0.0;
        }else{
            Mundo->evolut->acept[tempo] = 1.0;
            gsl_vector_swap( OpNew , Mundo->agente[node].opinion );
            Ef = Ei;
            hf = hi;
            ok = 0;
        }
    }

    if (tempo > 0 ) {
        if (ok == 0) {
            Mundo->evolut->mag[tempo] = Mundo->evolut->mag[tempo - 1];
            Mundo->evolut->erg[tempo] = Mundo->evolut->erg[tempo - 1];
        }else{
            Mundo->evolut->mag[tempo] = Mundo->evolut->mag[tempo - 1] + (hf - hi)/(double)Mundo->NUM;
            Mundo->evolut->erg[tempo] = Mundo->evolut->erg[tempo - 1] + Ef - Ei;
            //printf("%d %d %g %g\n",tempo,node ,Ef - Ei,(hf - hi)/(double)Mundo->NUM);
        }
    }else{
        double * mi;
        EvalAllOverlaps( Mundo, Mundo->issues->zeit , &mi );
        EvalEMTotalOffline ( Mundo, mi, Erg, &(Mundo->evolut->erg[0]), &(Mundo->evolut->mag[0]));
        free(mi);
    }

    //printf("%d %g %g %g\n",tempo, Mundo->evolut->erg[tempo], Mundo->evolut->mag[tempo],Mundo->evolut->acept[tempo]);

    gsl_vector_free(OpNew);
}
