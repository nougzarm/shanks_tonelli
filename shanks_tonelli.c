#include "shanks_tonelli.h"

// Fonctions intermediaires
int ordre_deux(int m){
    int i = 0;
    while (m % 2 != 0){
        i++;
        m = m/2;
    }
    return i;
}

int modulo(int a, int b){
    return a%b + (b * (a%b<0));
}

int puissance(int m, int e){
    if ( e==0 ){
        return 1;
    }
    else if (( e%2==0 )&( e!=0 )){
        return puissance(m*m, e/2);
    }
    else {
        return m*puissance(m*m, (e-1)/2);
    }
}

int puissance_mod(int m, int e, int p){
    int result = 1;
    for (int i = 1; i <= e; i++){
        result = modulo(result, p)*m;
    }
    return modulo(result, p);
}

// Donne l'inverse de a dans F_p
int inverse_mod(int a, int p){
    a = modulo(a, p);
    int r0 = p, r1 = a, r2 = r0%r1;
    int v0 = 0, v1 = 1, v2 = v0 - (r0/r1)*v1;
    while ( r2 != 0 ){
        r0 = r1;
        r1 = r2;
        r2 = modulo(r0, r1);
        v0 = v1;
        v1 = v2;
        v2 = v0 - (r0/r1)*v1;
    }
    v1 = modulo(v1, p);
    return v1;
}



int jacobi(int a, int b){
    a = modulo(a, b);
    
    int signe = 1;
    int inter_reserve = 0;  // réserve pour le swap

    // Boucle de la 'réduction' via loi de réciprocité quadratique
    while ( ( b%a != 0 )&&( a != 2 ) ){
        if ( a%2 == 0 ){
            a = a/2;
            if ( (modulo(b, 8) == 3) || (modulo(b, 8) == 5) ){
                signe = signe*(-1);
            }
        }
        else {
            if ( ((a-1)*(b-1))%8 != 0 ){
            signe = signe*(-1);
            }
            inter_reserve = a;
            a = modulo(b, a);
            b = inter_reserve; 
        }
    }

    if ( a == 1 ){
        return signe;
    }
    if ( a == 2 ){
        int c = 1;
        if ( (modulo(b, 8) == 3) || (modulo(b, 8) == 5) ){
            c = -1;
        }
        return c*signe;
    }
    else{
        return 0;
    }
}



int shanks_tonelli(int p, int a, int n){
    int alpha = ordre_deux(p-1);
    int s = (p-1)/puissance(2, alpha);
    int r = modulo(puissance(a, (s+1)/2), p);
    int b = modulo(puissance(n, s), p);
    int y = (r*r)*inverse_mod(a, p);
    int j; // à determiner

    int* j_binaire = calloc(alpha, sizeof(int));
    j_binaire[alpha-1] = 0; // une des deux racines

    if ( puissance_mod(y, puissance(2, alpha-2), p) == 1 ){
        j_binaire[0] = 0;
    }
    else {
        j_binaire[0] = 1;
    }

    j = j_binaire[0];

    for (int l = 0; l <= alpha-3; l++){
        int condition = puissance_mod(puissance(puissance(b, j), 2)*y, puissance(2, alpha-2-l-1), p);
        if ( condition == 1 ){
            j_binaire[l+1] = 0;
        }
        else {
            j_binaire[l+1] = 1;
        }
        j = j + puissance(2, l+1)*j_binaire[l+1];
    }

    j = j + puissance(2, alpha-1)*j_binaire[alpha-1];  // Dans le cas ou j_binaire[alpha-1] = 1

    free(j_binaire);
    int x = modulo(puissance_mod(b, j, p)*r, p);
    return x;
}