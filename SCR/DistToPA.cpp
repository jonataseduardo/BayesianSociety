#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_statistics.h>
#include "../SCR/NormalizaGSLHistograma.hpp"
#include "Struct.hpp"

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
        // printf("%g %g ", sqrt(D), KLbetas(a1,b1,a2,b2));

        fclose(fp);
        gsl_histogram_free( hpa );
    }

}
