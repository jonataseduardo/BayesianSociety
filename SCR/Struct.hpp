#include <igraph/igraph.h>
#include <gsl/gsl_vector.h>

struct StrBrain {
    double delta;
};

struct StrAgente {
    gsl_vector * opinion;
    StrBrain brain;
};

struct StrZeit {
    gsl_vector * zeit;
};

struct StrTempos {
    double step;
    int TotalTime; 
    int burn;
    int coleta;
};

struct StrEvolve {
    double * mag;
    double * vmag;
    double * susc;
    double * erg;
    double * c;
    double * eacept;
    double * bacept;
    double * nacept;
};

struct StrOnline {
    double * mag;
    double * erg;
    double * acept;
    int size;
    int tempo;
};

struct StrMundo {
    struct StrAgente * agente;
    struct StrZeit   * issues;
    struct StrTempos * MCTime;
    struct StrOnline * evolut;
    igraph_t  * graph;
    double beta;
    size_t NUM;
    size_t DIM;
    int NVIZ;
    double p;
    char name[200];
};
