/*
-----------------------------------------------------------------
-- File name : tableaux_2_dimensions.c 
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

typedef int tab[10][5];

int main(void)
{
     tab t;
     
     printf("Type tableaux  deux dimensions\n");
     printf("Taille d'un tableau d'entiers ([10][5]): %zu\n", sizeof(tab));
     printf("Adresse de t : %p\n", &t);
     printf("Adresse de t[0] : %p\n", &t[0]);
     printf("Adresse de t[0][0] : %p\n", &t[0][0]);
     printf("Adresse de t[1] : %p\n", &t[1]);
     printf("Adresse de t[0][4] : %p\n", &t[0][4]);
     printf("Adresse de t[1][0] : %p\n", &t[1][0]);
     printf("Adresse de t[0][5] : %p\n", &t[0][5]);
     printf("Adresse de t[-2][50] : %p\n", &t[-2][50]);
     return(0);
}
