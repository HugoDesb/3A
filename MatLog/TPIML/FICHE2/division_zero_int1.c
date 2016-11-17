/*
-----------------------------------------------------------------
-- File name : division_zero_int1.c
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

  printf ("Test division d'un entier par zero (quotient)\n");
  printf("Entrez un nombre entier : ");
  scanf("%d",&x);
  printf("%d / 0 = %d\n", x, x/y);
  printf ("Fin du programme division_zero_int1\n");
  return(0);
}

