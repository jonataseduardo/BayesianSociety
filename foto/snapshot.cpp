#include <stdio.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_statistics.h>
#include "../SCR/Struct.hpp"
#include "../SCR/StartGslRngSeed.hpp"
#include "../SCR/StartStrOnline.hpp"
#include "../SCR/DestroyStrOnline.hpp"
#include "../SCR/GenesisMaster.hpp"
#include "../SCR/EscolheDupla.hpp"
#include "../SCR/MetropolizOnline.hpp"
#include "../SCR/Armagedon.hpp"
#include "../SCR/EnerAndSfuncions.hpp"
#include "../SCR/PrintErg.hpp"
#include "../SCR/PrintMag.hpp"
#include "../SCR/PrintAutoCorr.hpp"
#include "../SCR/PrintEvolut.hpp"
#include "../SCR/PrintGSLHistogram.hpp"
#include "../SCR/EvalTempAutoCorrMag.hpp"
#include "../SCR/EvalTempAutoCorrErg.hpp"
#include "../SCR/GetSamplesEvolut.hpp"
#include "../SCR/UpdateHistMag.hpp"
#include "../SCR/NormalizaGSLHistograma.hpp"

int main(int argc, char **argv)
{
    
    gsl_rng *r;
    StartGslRngSeed( &r);

    int nbins = 400;
    gsl_histogram * h = gsl_histogram_alloc( nbins);
    //gsl_histogram_set_ranges_uniform( h, 0.0, 1.0);
    gsl_histogram_set_ranges_uniform( h, -1.0, 1.0);
    
    struct StrMundo * Mundo   = NULL;
    double th = .1;

    GenesisMaster(argc, argv, r, &Mundo );

    int NUM = Mundo->NUM;
    int prof, alun;

    for (int tempo = 0; tempo < (int)Mundo->evolut->size; tempo++) {
        EscolheDupla( Mundo->graph, r, &prof, &alun);
        MetropolizOnline(Mundo, alun,  ErgOptN1 , r);
        if ( tempo >= NUM*Mundo->MCTime->burn && tempo%(NUM*100) == 0 ) {
            UpdateHistMag( Mundo, Mundo->issues->zeit, h);
        }
    }

    EvalTempAutoCorrMag( Mundo, th,  NUM*Mundo->MCTime->coleta/20,
            Mundo->evolut->mag,
            Mundo->evolut->erg );

    NormalizaGSLHistograma( h );
    double sigma = gsl_histogram_sigma( h );

    PrintGSLHistogram( h, Mundo->name );        
    PrintAutoCorr( Mundo, th, NUM*Mundo->MCTime->coleta/5, 0 );
    PrintEvolut( Mundo, NUM*(Mundo->MCTime->burn+Mundo->MCTime->coleta/5), 0 );

    gsl_histogram_free( h );
    Armagedon( &Mundo );

    return 0;
}

