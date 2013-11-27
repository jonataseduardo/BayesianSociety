#include "Struct.hpp"

void DestroyStrOnline( struct StrOnline ** M)
{
    free((*M)->mag);
    free((*M)->erg);
    free((*M)->acept);
    free((*M));
}
