#include <stdio.h>
#include <math.h>
#include "../SCR/Struct.hpp"

void PrintEvolut( StrMundo * Mundo , int SIZE, int id)
{
    int NUM = Mundo->NUM;
    int burn = NUM*Mundo->MCTime->burn;

    int T = NUM*Mundo->MCTime->coleta;
    int step = (int)NUM*Mundo->MCTime->step;

    double xe = 1, xm = 1;

    FILE * fp;
    char name[100];
    sprintf(name,"ME_evolut_%s_%d.dat", Mundo->name,id);
    fp = fopen(name, "w");

    for (int i = NUM; i < SIZE; i+= step) {
        fprintf(fp," %d %g %g\n"
                , i/NUM - 1
                , Mundo->evolut->erg[i]
                , Mundo->evolut->mag[i]
               );
    }

    fclose(fp);
}
