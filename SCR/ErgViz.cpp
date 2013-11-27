#include <stdlib.h>
#include <igraph/igraph.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include "Struct.hpp"

void ErgViz( struct StrMundo * Mundo , int node, double (*Erg)(double, double, double), double * hout, double * Eout)
{
    igraph_vector_t neighbors;
    igraph_vector_init(&neighbors,1);
    igraph_neighbors(Mundo->graph,&neighbors,(igraph_integer_t)node ,IGRAPH_ALL);

    int viz, Nviz = igraph_vector_size(&neighbors);
    double E = 0, h, hviz;
    double delta = Mundo->agente[node].brain.delta;

    gsl_blas_ddot( Mundo->agente[node].opinion, Mundo->issues->zeit, &h );
    for ( int i = 0; i < Nviz; i++) {
        viz = VECTOR(neighbors)[i];
        gsl_blas_ddot( Mundo->agente[viz].opinion, Mundo->issues->zeit, &hviz );
        E += (*Erg)( delta, h, hviz);
    }
    igraph_vector_destroy(&neighbors);

    *Eout = E;
    *hout = h;
}
