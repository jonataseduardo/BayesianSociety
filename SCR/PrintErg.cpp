#include <stdio.h>
#include <gsl/gsl_blas.h>
#include "Struct.hpp"

void PrintErg (struct StrMundo * Mundo, double (*Erg)(double, double,double) )
{
    igraph_integer_t edges, edg, i, j;
    edges = igraph_ecount( Mundo->graph );

    double delta = Mundo->agente[0].brain.delta;
    double beta = Mundo->beta;
    double E = 0;
    double m[Mundo->NUM];

    FILE * fp;
    char name[100];
    sprintf(name,"ERG_%s.dat",Mundo->name);
    fp = fopen(name, "a+");

    for (int k = 0; k < Mundo->NUM; k++)
        gsl_blas_ddot( Mundo->agente[k].opinion , Mundo->issues->zeit , &m[k]);

    for ( edg = 0; edg < edges; edg++) {
        igraph_edge(Mundo->graph, edg, &i, &j);
        E = (*Erg)( delta, m[(int)i], m[(int)j]);
        fprintf(fp, "%g \n", E);
    }

    fclose(fp);
}
