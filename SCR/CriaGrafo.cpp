#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Struct.hpp"

void CriaGrafo ( struct StrMundo * Mundo, char gname[20], int ops ){

    igraph_integer_t NUM = Mundo->NUM;
    int nviz = Mundo->NVIZ;
    double p;

    if( ops == 4 ){
        p = Mundo->p > 1.0? (double)nviz/(double)NUM: Mundo->p;
        igraph_erdos_renyi_game( Mundo->graph, IGRAPH_ERDOS_RENYI_GNP, NUM, p,  IGRAPH_UNDIRECTED, IGRAPH_NO_LOOPS);
        sprintf(gname, "%s", "Arvore");
    }

    if( ops == 3 ){
        igraph_erdos_renyi_game( Mundo->graph, IGRAPH_ERDOS_RENYI_GNP, NUM, (double)nviz/(double)NUM, IGRAPH_UNDIRECTED, IGRAPH_LOOPS);
        sprintf( gname, "%s","Erdos");
    }

    if( ops == 2 ){
        igraph_barabasi_game( Mundo->graph, NUM, nviz/2 , NULL, 1, IGRAPH_UNDIRECTED);
        sprintf( gname, "%s","Barabasi" );
    }

    if( ops == 1 ){
        p = Mundo->p > 1.0? 0.1: Mundo->p;
        igraph_watts_strogatz_game( Mundo->graph, 2,(size_t)sqrt((double)NUM), 1, p);
        sprintf( gname, "%s","WattsStrogatz");
    }

    if( ops == 0 ){
        igraph_vector_t dimvector;
        igraph_vector_init(&dimvector, 2);
        VECTOR(dimvector)[0]= (size_t)sqrt((double)NUM);
        VECTOR(dimvector)[1]= (size_t)sqrt((double)NUM);
        igraph_lattice( Mundo->graph, &dimvector, 0, IGRAPH_UNDIRECTED, 0, 1);
        sprintf( gname,"%s","Lattice" );
    }
}

