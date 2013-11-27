#include <stdlib.h>
#include "DestroyStrOnline.hpp"
#include "Struct.hpp"

void Armagedon(struct StrMundo ** Mundo )
{
    // free agents
    for (int i = 0; i < (*Mundo)->NUM; i++) {
        gsl_vector_free( (*Mundo)->agente[i].opinion );
    }
    free((*Mundo)->agente);

    //free issues
    gsl_vector_free( (*Mundo)->issues->zeit );
    free( (*Mundo)->issues );

    //Inicializa vetores com as séries temporarais das variáveis de interesse
    DestroyStrOnline( &(*Mundo)->evolut);
    //DestroyStrEvolve( &(*Mundo)->evolut);

    //free time
    free((*Mundo)->MCTime);

    //free graph
    igraph_destroy((*Mundo)->graph);

    free((*Mundo));
}
