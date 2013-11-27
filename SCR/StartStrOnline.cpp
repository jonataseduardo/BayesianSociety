#include "Struct.hpp"

void StartStrOnline( struct StrOnline ** M, size_t size)
{
        (*M)         = (struct StrOnline *) malloc( sizeof(struct StrOnline) );
        (*M)->mag    = (double *)malloc(size*sizeof(double));
        (*M)->erg    = (double *)malloc(size*sizeof(double));
        (*M)->acept  = (double *)malloc(size*sizeof(double));
        (*M)->size   = size;
        (*M)->tempo  = 0;
}
