/*
-----------------------------------------------------------------
-- File name : tableaux_et_pointeurs.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h> /* pour malloc */


int main(void)
{

     int P[10];
     	int *Q ; 

     printf("Tableaux et pointeurs \n"); 
     printf("Taille de P : %zu\n", sizeof(P));
     printf("Taille de Q : %zu\n", sizeof(Q));
    
     printf("Valeur de P  : %p\n", P);
     printf("Valeur de Q avant malloc  : %p\n", Q);
     Q = (int *)malloc(10*sizeof(int));
     printf("Valeur de Q apres malloc  : %p\n", Q);
     
     printf("Adresse de P = %p, adresse de P[0] = %p\n", &P, &(P[0]));
     printf("Adresse de Q = %p, adresse de Q[0] = %p\n", &Q, &(Q[0]));
     return(0);
}
