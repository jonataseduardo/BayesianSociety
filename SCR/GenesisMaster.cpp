#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gsl/gsl_rng.h>
#include "Struct.hpp"
#include "CriaGrafo.hpp"
#include "SampleNormedRndVecWBias.hpp"
#include "StartStrOnline.hpp"


void GenesisMaster(int argc, char** argv, gsl_rng * r, struct StrMundo ** Mundo ){
    int Nargs = 12;
    if ( argc == Nargs) {

        (*Mundo)  = (struct StrMundo  *) malloc(sizeof(struct StrMundo));

        //Inicialisa os escalares
        int opGrafo     = atoi(argv[5]);
        (*Mundo)->DIM   = 5;
        (*Mundo)->NUM   = (size_t)atoi(argv[4]);
        (*Mundo)->NVIZ  = atoi(argv[3]);
        (*Mundo)->beta  = exp(atof(argv[2]));

        // Inicia o Grafo de suporte
        (*Mundo)->graph = (igraph_t *)malloc(sizeof(igraph_t));
        char gname[20];
        CriaGrafo ( *Mundo, gname, opGrafo);

        //double rho = atof(argv[1]);
        //double lambda = sqrt(1.0 - rho*rho)/rho;
        double lambda = atof(argv[1]);
        //Inisializa os vetores de opinião e estratégia cognitiva
        (*Mundo)->agente = (struct StrAgente *) malloc( (*Mundo)->NUM * sizeof(struct StrAgente) );
        for (int i = 0; i < (*Mundo)->NUM; i++) {
            (*Mundo)->agente[i].opinion = gsl_vector_alloc((*Mundo)->DIM);
            SampleNormedRndVecWBias((*Mundo)->agente[i].opinion, 1.0, r );
            (*Mundo)->agente[i].brain.delta = lambda;
        }

        //Inicializa o zeitgeist
        (*Mundo)->issues = (struct StrZeit *)malloc(sizeof(struct StrZeit));
        (*Mundo)->issues->zeit = gsl_vector_alloc((*Mundo)->DIM);
        gsl_vector_set_all((*Mundo)->issues->zeit,1.0/sqrt((double)(*Mundo)->DIM));

        //Inicializa os tempos
        (*Mundo)->MCTime            = (struct StrTempos *) malloc(sizeof(struct StrTempos));
        (*Mundo)->MCTime->step      = atof(argv[6]); // só é usado para separar duas medidas de autocorrelação
        (*Mundo)->MCTime->coleta    = atoi(argv[7]);
        (*Mundo)->MCTime->burn      = atoi(argv[8]);

        //Inicializa vetores com as séries temporarais das variáveis de interesse
        StartStrOnline( &(*Mundo)->evolut, 
                (size_t)((*Mundo)->MCTime->coleta + (*Mundo)->MCTime->burn)
                *(*Mundo)->NUM);
        //StartStrEvolve( &(*Mundo)->evolut, medidas);

        sprintf( (*Mundo)->name, "%s_K-%s_n-%s_TB-%s_TC-%s_stp-%s_B-%s_D-%s",
                gname, argv[4], argv[3], argv[8], argv[7], argv[6], 
                argv[2],argv[1]);
        //printf("%s\n",(*Mundo)->name);
        //sprintf( (*Mundo)->name, "%s_K-%s_n-%s_B-%s_D-%s_TT-%s_NC-%s_NE-%s_ID-%d",
                //gname, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], getpid());

    }else{
        printf(" The fowlling %d arguments are needed on the respctive order \n", Nargs);
        printf(" Graph Num Nviz Beta Delta Step TimeTest TauThreshold"
                                           "NMasters NExperiments NCollect \n");
        printf(" Faltam %d argumentos \n", Nargs - argc);
        exit(1);
    }
}
