/*
-----------------------------------------------------------------
-- File name : types_enum1.c
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

typedef enum{lundi, mardi, mercredi, jeudi, vendredi, samedi, dimanche} jds;

int main(void)
{
     
     printf("Type enum\n"); 
     printf("Taille du type enumere jds : %zu\n", sizeof(jds));
     printf("Valeur des elements de jds : \n");
     printf("lundi = %d \n", lundi);
     printf("mardi = %d \n", mardi);
     printf("mercredi = %d \n", mercredi);
     printf("jeudi = %d \n", jeudi);
     printf("vendredi = %d \n", vendredi);
     printf("samedi = %d \n", samedi);
     printf("dimanche = %d \n", dimanche);
     return(0);
}
