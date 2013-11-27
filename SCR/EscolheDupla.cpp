#include <igraph/igraph.h>
#include <gsl/gsl_rng.h>

void EscolheDupla( igraph_t *graph, gsl_rng * r, int *prof, int *alun ){
    double p;
    igraph_integer_t edges, edg, v1, v2;

    edges = igraph_ecount( graph );                 // conta o numero de arestas 
    edg = gsl_rng_uniform_int( r ,  (int)edges );   // escolhe uma aresta aleatoriamente
    igraph_edge(graph, edg, &v1, &v2);              // dado a aresta adquire os vertices 

    p = gsl_rng_uniform(r);
    if(p < 0.5 ){
        *prof = (int)v1;
        *alun = (int)v2;
    }else{
        *prof = (int)v2;
        *alun = (int)v1;
    }
}
