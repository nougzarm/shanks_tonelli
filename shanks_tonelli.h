#ifndef SHANKSTONELLI_INCLUDED
#define SHANKSTONELLI_INCLUDED

#include <stdio.h>
#include <stdlib.h>


// Fonctions intermediaires
int ordre_deux(int m);
int modulo(int m, int p);
int puissance(int m, int e);
int puissance_mod(int m, int e, int p);
int inverse_mod(int a, int p);


// SHANKS TONELLI 
int jacobi(int, int);
int shanks_tonelli(int p, int a, int n);

#endif // SHANKSTONELLI_INCLUDED