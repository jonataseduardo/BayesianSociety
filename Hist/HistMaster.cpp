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
#include "../SCR/PrintGSLHistogram.hpp"
#include "../SCR/EvalTempAutoCorrMag.hpp"
#include "../SCR/EvalTempAutoCorrErg.hpp"
#include "../SCR/GetSamplesEvolut.hpp"
#include "../SCR/UpdateHistMag.hpp"
#include "../SCR/NormalizaGSLHistograma.hpp"

void DistToPA(gsl_histogram * h, double mag, double sigma);


int main(int argc, char **argv)
{
    double th    = atof(argv[9]);
    int NMaster  = atoi(argv[10]);
    int NSamples = atoi(argv[11]);
    int coleta   = atoi(argv[7]);
    int NUM      = atoi(argv[4]);
    
    gsl_rng *r;
    StartGslRngSeed( &r);

    int nbins = 300;
    gsl_histogram * h = gsl_histogram_alloc( nbins);
    gsl_histogram_set_ranges_uniform( h, 0.0, 1.0);
    
    double x, * mt, * emt, * et, * eet;
    mt  = (double *) malloc(coleta*sizeof(double));
    emt = (double *) malloc(coleta*sizeof(double));
    et  = (double *) malloc(coleta*sizeof(double));
    eet = (double *) malloc(coleta*sizeof(double));
    
    struct StrOnline * sample = NULL;
    StartStrOnline( &sample, coleta*NMaster );

    char name[100];

    int n = 0, ns = 0;
    do{
        struct StrMundo * Mundo   = NULL;

        GenesisMaster(argc, argv, r, &Mundo );

        int NUM = Mundo->NUM;
        int burn = NUM*Mundo->MCTime->burn;
        int coleta = NUM*Mundo->MCTime->coleta;

        int prof, alun;
        double x;
        for (int tempo = 0; tempo < (int)Mundo->evolut->size; tempo++) {
            EscolheDupla( Mundo->graph, r, &prof, &alun);
            MetropolizOnline(Mundo, alun,  ErgOptN1 , r);
            //MetropolizOnline(Mundo, alun,  ErgOptN , r);
            //MetropolizOnline(Mundo, alun,  ErgCR , r);
            if ( tempo >= NUM*Mundo->MCTime->burn && tempo%(NUM*100) == 0 ) {
                UpdateHistMag( Mundo, Mundo->issues->zeit, h);
            }
        }

        //PrintAutoCorr( Mundo, -th, NUM*Mundo->MCTime->coleta/5, n );
        //EvalTempAutoCorrErg( Mundo, th,  NUM*Mundo->MCTime->coleta/20,
                //&et[n], &eet[n], &mt[n], &emt[n]);
        EvalTempAutoCorrMag( Mundo, th,  NUM*Mundo->MCTime->coleta/20,
                &mt[n], &emt[n]);
        if (n==0) {
            sprintf(name,"%s",Mundo->name);
        }
        ns += (int)(Mundo->MCTime->coleta/mt[n]) + 1 ;

        if (mt[n] < 2000.0) {
            GetSamplesEvolut( Mundo, mt[n], sample);
        }else{
            GetSamplesEvolut( Mundo, 2000.0, sample);
        }

        Armagedon( &Mundo );
        n++;
    }while(n < NMaster || ns < NSamples);
    
    NormalizaGSLHistograma( h );
    double sigma = gsl_histogram_sigma( h );

    PrintGSLHistogram( h, name );        

    double etau  = gsl_stats_mean(et,1,n);
    double eetau = gsl_stats_sd(et,1,n);
    double mtau  = gsl_stats_mean(mt,1,n);
    double emtau = gsl_stats_sd(mt,1,n);
    double mag   = gsl_stats_mean(sample->mag,1,sample->tempo);
    double vmag  = gsl_stats_variance(sample->mag,1,sample->tempo);
    double erg   = gsl_stats_mean(sample->erg,1,sample->tempo);
    double verg  = gsl_stats_variance(sample->erg,1,sample->tempo);
    double acpt  = gsl_stats_mean(sample->acept,1,sample->tempo);
    double vacpt = gsl_stats_variance(sample->acept,1,sample->tempo);
    
    printf("%g %g %g %g %g %g %g %g %g %g %g %d %d ", 
            etau, eetau, mtau, emtau,
            mag, vmag, sigma, erg, verg,
            acpt, vacpt, n, sample->tempo);

    DistToPA(h,mag,sigma);

    DestroyStrOnline(&sample);
    free(mt  ); 
    free(emt );
    free(et  );
    free(eet );
    gsl_histogram_free( h );

    return 0;
}

void DistToPA(gsl_histogram * h, double mag, double sigma)
{

double m1 = 0.5*mag + 0.5;
double s1 = 0.25*sigma;
double n1 = m1*(1. - m1)/s1 - 1.; 
double a1 = m1*n1;
double b1 = (1. - m1)*n1;

    for (int pa = 1; pa < 8; pa++) {
        char line[80];
        double x;
        double data[6000];
        int size = 0;
        int nbins = h->n;
        gsl_histogram * hpa = gsl_histogram_alloc( nbins);
        gsl_histogram_set_ranges_uniform( hpa, 0.0, 1.0);

        char fname[50];
        sprintf(fname,"/home/jonatas/mzanlz/mZ_pa%d.dat",pa);
        FILE * fp;
        fp = fopen(fname,"rt");
        while(fgets(line,80,fp) != NULL){
            x = atof(line); 
            size++;
            data[size] = x;
            gsl_histogram_increment( hpa, x);
        }
        double m2 = 0.5*gsl_stats_mean( data, 1, size ) + 0.5;
        double s2 = 0.25*gsl_stats_variance( data, 1, size );
        double n2 = m2*(1. - m2)/s2 - 1.; 
        double a2 = m2*n2;
        double b2 = (1. - m2)*n2;


        NormalizaGSLHistograma( hpa );
        //char hname[100];
        //sprintf(hname,"pa%d",pa);
        //PrintGSLHistogram( hpa, hname );        

        gsl_histogram_sub( hpa, h);
        double D = 0;
        for (size_t i = 0; i < nbins; i++) {
            D += gsl_histogram_get( hpa , i )*gsl_histogram_get( hpa , i );
        }
        printf("%g %g ", sqrt(D), KLbetas(a1,b1,a2,b2));

        fclose(fp);
        gsl_histogram_free( hpa );
    }

}
