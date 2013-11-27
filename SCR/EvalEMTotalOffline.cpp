#include "Struct.hpp"

void EvalEMTotalOffline 
(struct StrMundo * Mundo, double * m, double (*Erg)(double, double,double), double * erg, double * mag)
{
    igraph_integer_t edges, edg, i, j;
    edges = igraph_ecount( Mundo->graph );
    double * Eij = (double *)malloc((size_t)edges*sizeof(double));

    double delta = Mundo->agente[0].brain.delta;
    double beta = Mundo->beta;
    double E = 0, mi = 0;

    for ( edg = 0; edg < edges; edg++) {
        igraph_edge(Mundo->graph, edg, &i, &j);
        Eij[(int)edg] = (*Erg)( delta, m[(int)i], m[(int)j]);
        E += Eij[(int)edg];
    }
    for ( int k = 0; k < Mundo->NUM; k++) {
        mi += m[k];
    }

    *mag = mi/(double)Mundo->NUM;
    *erg = E;

    free(Eij);
}
