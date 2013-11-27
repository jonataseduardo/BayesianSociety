#include <stdio.h>
#include <gsl/gsl_histogram.h>

void PrintGSLHistogram( gsl_histogram * h, char name[] )
{
    FILE * fp1;
    char fname[300];
    sprintf( fname, "%s_%s.dat","HIST", name );
    fp1 = fopen( fname, "w");
    gsl_histogram_fprintf(fp1,h,"%g","%g");
    fclose(fp1);
}
