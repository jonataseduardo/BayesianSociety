#include <stdlib.h>
#include <igraph/igraph.h>
#include <gsl/gsl_statistics.h>
#include "Struct.hpp"
#include <stdlib.h>
#include <gsl/gsl_statistics.h>


void EvalErg (struct StrMundo * Mundo, double * m, double (*Erg)(double, double,double), double * erg, double * c)
{
    igraph_integer_t edges, edg, i, j;
    edges = igraph_ecount( Mundo->graph );
    double * Eij = (double *)malloc((size_t)edges*sizeof(double));

    double delta = Mundo->agente[0].brain.delta;
    double beta = Mundo->beta;

    for ( edg = 0; edg < edges; edg++) {
        igraph_edge(Mundo->graph, edg, &i, &j);
        Eij[(int)edg] = (*Erg)( delta, m[(int)i], m[(int)j]);
    }

    *erg= gsl_stats_mean(Eij, 1,(size_t)edges);
    *c= gsl_stats_variance(Eij,1,(size_t)edges)*beta*beta;
    free(Eij);
}
