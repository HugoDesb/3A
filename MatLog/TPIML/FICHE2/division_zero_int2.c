/*
-----------------------------------------------------------------
-- File name : division_zero_int2.c 
-- Objet : TP Interface Matériel Logiciel - Fiche 2
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  int x ;
  int y = 0;

  printf ("Test division d'un entier par zero (reste) \n");
  printf ("Entrez un nombre entier : ");
  scanf("%d",&x);
  printf("%d modulo 0 =  %d\n", x, x%y);
  printf ("Fin du programme division_zero_int2\n");
  return(0);
}

